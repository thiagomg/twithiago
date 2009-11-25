#include "QTwitPicture.h"

QTwitPicture::QTwitPicture()
{
}

QTwitPicture::QTwitPicture(const QImage &img) :QImage(img)
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

QTwitPicture QTwitPicture::resize()
{
	QImage img = scaled(48, 48, Qt::IgnoreAspectRatio);
	QTwitPicture pic(img);
	pic.setUsername(getUsername());

	return pic;
}
