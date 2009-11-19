#pragma once

#include <QString>

class Credentials
{
public:
    Credentials();
	Credentials(const QString &username, const QString &password);
	~Credentials();

	void setUsername(const QString &username);
	void setPassword(const QString &password);
	const QString & getUsername() const;
	const QString & getPassword() const;

	bool hasUserSet() const;

	void loadConfig();

private:
	QString _username;
	QString _password;

};

