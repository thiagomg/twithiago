#ifndef QTWITPICTURE_H
#define QTWITPICTURE_H

#include <QImage>

class QTwitPicture : public QImage
{
public:
    QTwitPicture();

	void setUsername(const QString &username);
	const QString &getUsername() const;

private:
	QString _username;

};

#endif // QTWITPICTURE_H
