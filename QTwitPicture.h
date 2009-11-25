#ifndef QTWITPICTURE_H
#define QTWITPICTURE_H

#include <QImage>

class QTwitPicture : public QImage
{
public:
    QTwitPicture();
	QTwitPicture(const QImage &img);

	void setUsername(const QString &username);
	const QString &getUsername() const;

	QTwitPicture resize();

private:
	QString _username;

};

#endif // QTWITPICTURE_H
