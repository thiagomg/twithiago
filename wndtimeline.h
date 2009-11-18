#ifndef WNDTIMELINE_H
#define WNDTIMELINE_H

#include <QtGui/QMainWindow>
#include <QFrame>

#include "Twitter.h"

namespace Ui
{
    class WndTimeline;
}

class WndTimeline : public QMainWindow
{
    Q_OBJECT

public:
    WndTimeline(QWidget *parent = 0);
    ~WndTimeline();

protected:
	QString _changeLinks(const QString &text);
	int _endTok(const QString &text, int pos);
	void _setWaiting(bool waiting);

private:
	enum TIPO_REQ {
		_TIPO_NADA,
		_TIPO_TIMELINE,
		_TIPO_DIRECT
	};

    Ui::WndTimeline *ui;
	Twitter _twitter;
	QList< QFrame* > _frameList;
	TIPO_REQ _tipoReq;

private slots:
	void onTimeline();
	void onMentions();
	void onDirect();
	void onFriendsTimeline(Timeline *timeLine, int error);

	void linkClicked(QString desc);

};

#endif // WNDTIMELINE_H
