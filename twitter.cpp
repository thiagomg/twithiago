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

	QUrl netUrl( url );

	_checkProxy(netUrl); //Use proxy ?

	QNetworkRequest request(url);

	QString login( _twitterUser );
	QString password( _twitterPwd );
	QByteArray auth = login.toUtf8() + ":" + password.toUtf8();
	auth = auth.toBase64().prepend( "Basic " );

	request.setRawHeader( "Authorization", auth );

	nam->get(request);

	return true;
}

bool Twitter::_postUpdate()
{
	return false;
}

void Twitter::onNetRecv(QNetworkReply *reply)
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
