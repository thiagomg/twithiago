#include "twitter.h"

#include <QXmlSimpleReader>
#include <QBuffer>

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
	request.setAttribute( ATTR_TIPO, _attr_timeline );

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
	postData.append( "&source=Twithiago" );

	request.setAttribute( ATTR_TIPO, _attr_update );

	nam->post(request, postData);

	return true;
}


const QImage *Twitter::getPicture(const QString &userName, const QString &url)
{
	QUrl netUrl( url );

	QMap<QString, QImage>::iterator it = _mapPics.find( netUrl.toString(QUrl::None) );
	if( it != _mapPics.end() ) {
		QImage &img = *it;
		return &img;
	}

	_checkProxy(netUrl); //Use proxy ?

	QNetworkRequest request(netUrl);
	request.setAttribute( ATTR_TIPO, _attr_picture );
	request.setAttribute( ATTR_PIC_URL, url );
	request.setAttribute( ATTR_USER, userName );
	
	nam->get(request);

	return NULL;
}

void Twitter::onNetRecv(QNetworkReply *reply)
{
	int tipo = reply->attribute( ATTR_TIPO ).toInt();
	switch( tipo ) {
	case _attr_timeline:
		_processTimeline(reply);
		break;
	case _attr_picture:
		_processPictures(reply);
		break;
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
		//ui->edtResult->setPlainText(s);
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
	}
}

void Twitter::_processPictures(QNetworkReply *reply)
{
	QString userName = reply->attribute( ATTR_USER ).toString();

	QString url = reply->url().toString(QUrl::None);
	qDebug() << "URL: " << url;

	QMap<QString, QImage>::iterator it = _mapPics.find(url);
	if( it != _mapPics.end() ) {
		//already there
		return;
	}

	QImage img;
	it = _mapPics.insert( url, img );

	QImage &imgIns = *it;
	imgIns.loadFromData( reply->readAll() );

	emit onFriendPicture(userName, imgIns);
}
