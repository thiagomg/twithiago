#ifndef TIMELINE_H
#define TIMELINE_H

#include <QMap>
#include <QVector>
#include <QString>

class Timeline
{
public:
    Timeline();
	~Timeline();

	typedef QMap<QString, QString> MapStatus;
	typedef QMap<QString, QString>::const_iterator StatusIterator;

private:
	QVector<MapStatus *> _vecStatus;
	QString _empty;

public:
	int getCount() const;
	const QString & getParam(int line, const QString &paramName) const;
	void pushMap(MapStatus *map);

	void dump();

};

#endif // TIMELINE_H
