#include "twitter.h"

#include <QXmlSimpleReader>
#include <QBuffer>
#include <QMessageBox>

//#include <QFile>
//#include <QTextStream>

#include "friendlisthandler.h"


void Twitter::setProxy(const QString &user, const QString &pwd)
{
	_proxyUser = user;
	_proxyPwd = pwd;
}

void Twitter::setTwitterAccount(const QString &user, const QString &pwd)
{
	_twitterUser = user;
	_twitterPwd = pwd;
}

bool Twitter::getFriendsTimeline(int count)
{
	return _getTimeline( _timelineUrl, count );
}

bool Twitter::getMentionsTimeline(int count)
{
	return _getTimeline( _mentionsUrl, count );
}

bool Twitter::getDirectsTimeline(int count)
{
	return _getTimeline( _directsUrl, count );
}

bool Twitter::_checkProxy(QUrl &netUrl)
{
	if( _proxyUser.size() > 0 ) {
		QNetworkProxyQuery query(netUrl);
		QList<QNetworkProxy> list = QNetworkProxyFactory::systemProxyForQuery(query);

		if( list.size() > 0 ) {
			QNetworkProxy &proxy = *(list.begin());
			proxy.setUser( _proxyUser );
			proxy.setPassword( _proxyPwd );
			nam->setProxy( proxy );
		}

	}
	return true;
}

bool Twitter::_getTimeline(const QString &url, int count)
{
	QString twitterUrl;

	twitterUrl = url + QString("?count=%1").arg( count );

	QUrl netUrl( twitterUrl );

	_checkProxy(netUrl); //Use proxy ?

	QNetworkRequest request(netUrl);

	QString login( _twitterUser );
	QString password( _twitterPwd );
	QByteArray auth = login.toUtf8() + ":" + password.toUtf8();
	auth = auth.toBase64().prepend( "Basic " );

	request.setRawHeader( "Authorization", auth );
	request.setAttribute( ATTR_TIPO, 101 );

	nam->get(request);

	return true;
}

bool Twitter::postUpdate(const QString &data, quint64 inReplyTo)
{
	//TODO: Fazer o máx de requests por minuto
	QString twitterUrl;

	twitterUrl = _updateUrl;

	QUrl netUrl( twitterUrl );

	_checkProxy(netUrl); //Use proxy ?

	QNetworkRequest request(netUrl);

	QString login( _twitterUser );
	QString password( _twitterPwd );
	QByteArray auth = login.toUtf8() + ":" + password.toUtf8();
	auth = auth.toBase64().prepend( "Basic " );

	request.setRawHeader( "Authorization", auth );

	QByteArray postData( "status=" );
	postData.append( data.toUtf8().toPercentEncoding() );
	if ( inReplyTo != 0 ) {
		postData.append( "&in_reply_to_status_id=" + QByteArray::number( inReplyTo ) );
	}
	postData.append( "&source=Katapulto" );

	request.setAttribute( ATTR_TIPO, 102 );

	nam->post(request, postData);

	return true;
}


const QTwitPicture *Twitter::getPicture(const QString &userName, const QString &url)
{
	QUrl netUrl( url );

	QString urlImg = netUrl.toString(QUrl::None);
	QMap<QString, QTwitPicture>::iterator it = _mapPics.find( urlImg );
	if( it != _mapPics.end() ) {
		QTwitPicture &pic = *it;
		return &pic;
	} else {
		QTwitPicture pic;
		pic.setUsername(userName);
		_mapPics.insert(url, pic);
	}

	_checkProxy(netUrl); //Use proxy ?

	QNetworkRequest request(netUrl);
	request.setAttribute( ATTR_TIPO, 103 );

	nam->get(request);

	return NULL;
}

void Twitter::onNetRecv(QNetworkReply *reply)
{
	QString url = reply->url().toString(QUrl::None);
	QString upUrl = url.toUpper();
	qDebug() << "Twitter::onNetRecv" << url;

	if( url.contains(_timelineUrl) || url.contains(_mentionsUrl) || url.contains(_directsUrl) ) {
		_processTimeline(reply);
	} else if( url.endsWith(".jpg", Qt::CaseInsensitive) || url.endsWith(".png", Qt::CaseInsensitive)  || url.endsWith(".gif", Qt::CaseInsensitive) ) {
		_processPictures(reply);
	} else if( url.contains(_updateUrl) ) {
		_processUpdate(reply);
	}
}

void Twitter::_processTimeline(QNetworkReply *reply)
{
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

	//qDebug() << "ERROR: " << reply->error() << " - " << reply->errorString();

	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray bytes = reply->readAll();
		QString s(bytes);

		/*
		{
			QFile f("timeline.xml");
			if( f.open(QIODevice::WriteOnly) ) {
				QTextStream ts(&f);
				ts << s;
				f.close();
			}
		}*/

		emit onFriendsTimelineXML(s, 0);

		QXmlSimpleReader reader;
		QBuffer buffer(&bytes);
		QXmlInputSource input( &buffer );
		FriendListHandler handler;
		reader.setContentHandler(&handler);
		reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData", false);
		reader.parse(&input);

		emit onFriendsTimeline( handler.getTimeline(), 0 );
	}
	else
	{
		emit onFriendsTimelineXML(reply->errorString(), 1);
		emit onFriendsTimeline(NULL, 1);
		emit onError(reply->error(), reply->errorString());
	}
}

void Twitter::_processPictures(QNetworkReply *reply)
{
	QString url = reply->url().toString(QUrl::None);
	qDebug() << "URL: " << url;

	QMap<QString, QTwitPicture>::iterator it = _mapPics.find(url);
	if( it == _mapPics.end() ) {
		//Error!!!!!
		QMessageBox::critical(NULL, "Erro", "Erro relacionando imagem");
		return;
	}

	QTwitPicture &img = it.value();
	bool ret = img.loadFromData( reply->readAll() );

	if( !ret ) {
		QMessageBox::critical(NULL, "Erro carregando imagem", "Erro carregando imagem " + url);
	} else {
		img = img.resize();
		emit onFriendPicture(img);
	}
}

void Twitter::_processUpdate(QNetworkReply *reply)
{
	QString url = reply->url().toString(QUrl::None);
	qDebug() << "URL: " << url;

	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray bytes = reply->readAll();
		QString s(bytes);
		QXmlSimpleReader reader;
		QBuffer buffer(&bytes);
		QXmlInputSource input( &buffer );
		FriendListHandler handler;
		reader.setContentHandler(&handler);
		reader.setFeature("http://trolltech.com/xml/features/report-whitespace-only-CharData", false);
		reader.parse(&input);

		emit onUpdate(handler.getTimeline(), 0 );
	}
	else
	{
		emit onUpdate(NULL, reply->error());
	}
}
