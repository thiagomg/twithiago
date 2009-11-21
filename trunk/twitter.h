#pragma once

#include <QtNetwork>
#include <QObject>

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
		_directsUrl = "http://twitter.com/direct_messages.xml";

		connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetRecv(QNetworkReply*)));
	}
	~Twitter() {}

	bool getFriendsTimeline(int count=20);
	bool getMentionsTimeline(int count=20);
	bool getDirectsTimeline(int count=20);

	void setProxy(const QString &user, const QString &pwd);
	void setTwitterAccount(const QString &user, const QString &pwd);

protected:
	bool _getTimeline(const QString &url, int count);
	bool _postUpdate();
	bool _checkProxy(QUrl &netUrl);

signals:
	void onFriendsTimelineXML(const QString &timeLine, int error);
	void onFriendsTimeline(Timeline *timeLine, int error);

private slots:
	void onNetRecv(QNetworkReply *reply);

private:
	QNetworkAccessManager *nam;
	QString _timelineUrl;
	QString _mentionsUrl;
	QString _directsUrl;

	QString _proxyUser;
	QString _proxyPwd;
	QString _twitterUser;
	QString _twitterPwd;

};

