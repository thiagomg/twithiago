#include "Timeline.h"

#include <QDebug>

Timeline::Timeline()
{
}

Timeline::~Timeline()
{
	QVector< MapStatus* >::iterator it;
	for( it = _vecStatus.begin(); it != _vecStatus.end(); it++ ) {
		MapStatus *map = *it;
		delete map;
	}
}

void Timeline::pushMap(MapStatus *map)
{
	_vecStatus.push_back(map);
}

const QString & Timeline::getParam(int line, const QString &paramName) const
{
	const MapStatus *map = _vecStatus.at(line);
	StatusIterator it = map->find(paramName);
	if( it == map->end() ) {
		return _empty;
	}
	return it.value();
}

int Timeline::getCount() const
{
	return _vecStatus.size();
}

void Timeline::dump()
{
	int cnt = 0;
	for(QVector<MapStatus *>::const_iterator itv= _vecStatus.constBegin(); itv != _vecStatus.constEnd(); itv++) {

		cnt++;
		qDebug() << "-- " << cnt << " ------------------------------";

		MapStatus *map = *itv;
		StatusIterator it = map->constBegin();
		qDebug() << *it;
		for(; it != map->constEnd(); it++) {
			qDebug() << "[" << it.key() << ": " << it.value() << "]";
		}

	}
}
