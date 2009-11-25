#include "QTwitPicture.h"

QTwitPicture::QTwitPicture()
{
}

void QTwitPicture::setUsername(const QString &username)
{
	_username = username;
}

const QString &QTwitPicture::getUsername() const
{
	return _username;
}
