#ifndef WNDTIMELINE_H
#define WNDTIMELINE_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QRubberBand>
#include <QPair>

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
	QString _cleanLink(const QString &tok);

	void _setWaiting(bool waiting);

	bool _checkCredentials();

	void _createItem(int pos, const QString &id, const QString &user, const QString &picUrl, const QString &text, const Timeline &timeline);
	void _updateItem(int pos, const QString &id, const QString &user, const QString &picUrl, const QString &text, const Timeline &timeline);
	QString _getItem(int pos);

	const QImage *_getPicture(const QString &user, const QString &picUrl);
	void _showUpdate();
	void _checkMsgList();

	//Parsers --------------------------------------------
	QString _parseReply(const QString &cmd);
	void _parseTag(const QString &tag);
	QString _parseRT(const QString &msgNum);
	//====================================================

	//System Tray ----------------------
	void _createSystray();
	//==================================

	QRubberBand *rubberBand;
	QPoint _origin;
	virtual void mouseMoveEvent ( QMouseEvent * event );
	virtual void mousePressEvent ( QMouseEvent * event );
	virtual void mouseReleaseEvent ( QMouseEvent * event );

private:
	enum TIPO_REQ {
		_TIPO_NADA,
		_TIPO_TIMELINE,
		_TIPO_DIRECT
	};

	enum TELA_ATUAL {
		_TELA_NADA,
		_TELA_TIMELINE,
		_TELA_MENTIONS,
		_TELA_DIRECT,
		_TELA_USER
	};

    Ui::WndTimeline *ui;
	Twitter _twitter;

	typedef QPair<QLabel *, QLabel *> FrameItem;
	typedef QList< FrameItem > FrameList;
	FrameList _frameList;
	QVector< QString > _msgList;
	TIPO_REQ _tipoReq;

	Credentials _credentials;

	int _telaAtual;
	int _inReplyTo;

	QTimer timerRefresh;

	//System Tray ----------------------
	QSystemTrayIcon *systray;
	QMenu   *trayMenu;
	QAction *actShowHide;
	QAction *actExit;
	//==================================

private slots:
	void on_txtUpdate_textChanged();
	void on_actionUpdate_triggered();
	void onActionSairTriggered();
	void on_actionConfigurar_triggered();
	void onActionShowHideTriggered();
	void onTimeline();
	void onMentions();
	void onDirect();
	void onFriendsTimeline(Timeline *timeLine, int error);
	void onFriendPicture(const QTwitPicture &pic);
	void onUpdatePressed();
	void onCancelPressed();
	void onUpdate(Timeline *timeLine, int error);
	void onError(QNetworkReply::NetworkError error, const QString &errorString);

	void linkClicked(QString desc);

	void onRefreshTimeline();

	//SYSTRAY
	void messageClicked();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);


};

#endif // WNDTIMELINE_H
