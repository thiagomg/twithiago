#pragma once

#define CONFIG Config::getInstance()

#include <QMap>
#include <QString>
#include <QSettings>

class Config
{
private:
    Config();

public:

	static Config &getInstance();

	QString getUsername();
	void setUsername(const QString &username);
	QString getPassword();
	void setPassword(const QString &password);

	QString getProxyUsername();
	void setProxyUsername(const QString &username);
	QString getProxyPassword();
	void setProxyPassword(const QString &password);

protected:
	QString getParam(const QString &paramName) const;
	void setParam(const QString &paramName, const QString &paramValue);

private:
	typedef QMap<QString, QString> MapConfig;
	MapConfig _mapConfig;
	bool _configLoaded;

	QSettings _settings;

};
