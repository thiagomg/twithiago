#include "friendlisthandler.h"

FriendListHandler::FriendListHandler()
{
	_timeline = NULL;
}

FriendListHandler::~FriendListHandler()
{
}

bool FriendListHandler::startDocument()
{
	_inStatus = false;
	_inUser = false;
	_level = 0;
	_pMapStatus = NULL;
	_timeline = new Timeline();

	return true;
}

bool FriendListHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
	if( localName == "statuses" || localName == "direct-messages" ) return true;

	if( localName == "status" || localName == "direct_message" ) {
		_pMapStatus = new Timeline::MapStatus();
		_timeline->pushMap( _pMapStatus );
	} else {
		_currentTagList.append(localName);
	}
	return true;
}

bool FriendListHandler::endElement( const QString &namespaceURI, const QString &localName, const QString &qName)
{
	if( localName == "statuses" || localName == "direct-messages" ) return true;

	QString currentTag = _currentTagList.join("_");

	if( _pMapStatus != NULL ) {
		if( currentTag.size() > 0 ) {
			_pMapStatus->insert( currentTag, _currentText );
		}
	}

	_currentText = "";

	if( localName != "status" && localName != "direct_message" ) {
		_currentTagList.pop_back();
	}

	return true;
}

bool FriendListHandler::characters(const QString& ch)
{
	_currentText += ch;
	return true;
}

bool FriendListHandler::endDocument()
{
        _timeline->dump();

	return true;
}
