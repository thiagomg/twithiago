#ifndef TIMELINE_H
#define TIMELINE_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QDebug>

class Timeline
{
public:
    Timeline();
	~Timeline();

	typedef QMap<QString, QString> MapStatus;
	typedef QMap<QString, QString>::const_iterator StatusIterator;

	static QString trocaMes(QString dateTime)
	{
		dateTime.replace("Jan ", "01 ");
		dateTime.replace("Feb ", "02 ");
		dateTime.replace("Mar ", "03 ");
		dateTime.replace("Apr ", "04 ");
		dateTime.replace("May ", "05 ");
		dateTime.replace("Jun ", "06 ");
		dateTime.replace("Jul ", "07 ");
		dateTime.replace("Aug ", "08 ");
		dateTime.replace("Sep ", "09 ");
		dateTime.replace("Oct ", "10 ");
		dateTime.replace("Nov ", "11 ");
		dateTime.replace("Dec ", "12 ");
		return dateTime;
	}

	static QString cleanDateTime(const QString dt)
	{
		QString ret;
		ret = dt.mid(4);
		ret = ret.left(ret.size() - 10) + ret.right(4);
		return trocaMes(ret);
	}


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
