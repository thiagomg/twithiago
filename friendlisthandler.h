#ifndef FRIENDLISTHANDLER_H
#define FRIENDLISTHANDLER_H

#include <QXmlDefaultHandler>
#include "Timeline.h"

class FriendListHandler : public QXmlDefaultHandler
{
public:
    FriendListHandler();
	~FriendListHandler();

	bool startDocument();
	bool endElement( const QString &namespaceURI, const QString &localName, const QString &qName);
	bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
	bool characters(const QString& ch);
	bool endDocument();

private:

	QStringList _currentTagList;
	QString _currentText;

	bool _inStatus;
	bool _inUser;
	Timeline *_timeline;
	Timeline::MapStatus *_pMapStatus;
	int _level;

public:
	inline Timeline *getTimeline() { return _timeline; }

};

#endif // FRIENDLISTHANDLER_H
