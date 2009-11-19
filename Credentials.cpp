#include "Credentials.h"
#include "Config.h"

Credentials::Credentials()
{
}

Credentials::Credentials(const QString &username, const QString &password)
{
	_username = username;
	_password = password;
}

Credentials::~Credentials()
{
}


void Credentials::setUsername(const QString &username)
{
	_username = username;
}

void Credentials::setPassword(const QString &password)
{
	_password = password;
}

const QString & Credentials::getUsername() const
{
	return _username;
}

const QString & Credentials::getPassword() const
{
	return _password;
}

bool Credentials::hasUserSet() const
{
	if( _username.size() > 0 )
		return true;
	return false;
}

void Credentials::loadConfig()
{
	_username = CONFIG.getUsername();
	_password = CONFIG.getPassword();
}
