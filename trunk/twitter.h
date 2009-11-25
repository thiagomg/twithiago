#pragma once

#include <QtNetwork>
#include <QObject>
#include <QImage>
#include "QTwitPicture.h"

#include "Timeline.h"

class Twitter : public QObject
{
	Q_OBJECT

public:
        Twitter(QObject *parent = 0) :
                QObject(parent)
        {
		nam = new QNetworkAccessManager(this);

		_timelineUrl = "http://twitter.com/statuses/friends_timeline.xml";
		_mentionsUrl = "http://twitter.com/statuses/mentions.xml";
		_updateUrl = "http://twitter.com/statuses/update.xml";
		_directsUrl = "http://twitter.com/direct_messages.xml";

		connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetRecv(QNetworkReply*)));
	}
	~Twitter() {}

	void setProxy(const QString &user, const QString &pwd);
	void setTwitterAccount(const QString &user, const QString &pwd);

	bool getFriendsTimeline(int count=20);
	bool getMentionsTimeline(int count=20);
	bool getDirectsTimeline(int count=20);
	const QTwitPicture *getPicture(const QString &userName, const QString &url);
	bool postUpdate(const QString &data, quint64 inReplyTo);

protected:
	bool _getTimeline(const QString &url, int count);
	bool _checkProxy(QUrl &netUrl);

	void _processTimeline(QNetworkReply *reply);
	void _processPictures(QNetworkReply *reply);

signals:
	void onFriendsTimelineXML(const QString &timeLine, int error);
	void onFriendsTimeline(Timeline *timeLine, int error);
	void onFriendPicture(const QTwitPicture &img);

private slots:
	void onNetRecv(QNetworkReply *reply);

private:
	static const QNetworkRequest::Attribute ATTR_TIPO = (QNetworkRequest::Attribute)(QNetworkRequest::User+1);
	static const QNetworkRequest::Attribute ATTR_PIC_URL = (QNetworkRequest::Attribute)(QNetworkRequest::User+2);
	static const QNetworkRequest::Attribute ATTR_USER = (QNetworkRequest::Attribute)(QNetworkRequest::User+3);

	enum AttrType {
		_attr_timeline = 101,
		_attr_update,
		_attr_picture
	};

private:
	QNetworkAccessManager *nam;
	QString _timelineUrl;
	QString _mentionsUrl;
	QString _directsUrl;
	QString _updateUrl;

	QString _proxyUser;
	QString _proxyPwd;
	QString _twitterUser;
	QString _twitterPwd;

	QMap<QString, QTwitPicture> _mapPics;

};

