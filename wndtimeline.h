#ifndef WNDTIMELINE_H
#define WNDTIMELINE_H

#include <QtGui/QMainWindow>
#include <QFrame>

#include "twitter.h"
#include "Credentials.h"

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

	bool _checkCredentials();

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

	Credentials _credentials;

private slots:
	void on_actionSair_triggered();
	void on_actionConfigurar_triggered();
	void onTimeline();
	void onMentions();
	void onDirect();
	void onFriendsTimeline(Timeline *timeLine, int error);

	void linkClicked(QString desc);

};

#endif // WNDTIMELINE_H
