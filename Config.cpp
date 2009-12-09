#include "Config.h"

#define TWITTER_USER "twitter_user"
#define TWITTER_PASSWORD "twitter_password"
#define PROXY_USER "proxy_user"
#define PROXY_PASSWORD "proxy_password"

static Config *_this = 0;

Config::Config() :
	_settings(QString("Blogaro"), QString("Katapulto"), 0)
{
	_configLoaded = false;
}

Config &Config::getInstance()
{
	if( _this == 0 ) {
		_this = new Config();
	}
	return *_this;
}

QString Config::getParam(const QString &paramName) const
{
	return _settings.value(paramName, "").toString();
}

void Config::setParam(const QString &paramName, const QString &paramValue)
{
	_settings.setValue(paramName, paramValue);
}

QString Config::getUsername()
{
	return getParam(TWITTER_USER);
}

void Config::setUsername(const QString &username)
{
	setParam(TWITTER_USER, username);
}

QString Config::getPassword()
{
	return getParam(TWITTER_PASSWORD);
}

void Config::setPassword(const QString &password)
{
	setParam(TWITTER_PASSWORD, password);
}

QString Config::getProxyUsername()
{
	return getParam(PROXY_USER);
}

void Config::setProxyUsername(const QString &username)
{
	setParam(PROXY_USER, username);
}

QString Config::getProxyPassword()
{
	return getParam(PROXY_PASSWORD);
}

void Config::setProxyPassword(const QString &password)
{
	setParam(PROXY_PASSWORD, password);
}

