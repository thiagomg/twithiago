#include "wndtimeline.h"
#include "ui_wndtimeline.h"

#include "frmconfig.h"
#include "Config.h"
#include "FrmNotification.h"

#include <QtGui>

//TODO: pass to config
#define MSG_COUNT 50

//#define _DISABLE_TIMER

WndTimeline::WndTimeline(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::WndTimeline),
	timerRefresh(this)
{
    ui->setupUi(this);

	connect(ui->btnTimeline, SIGNAL(clicked()), this, SLOT(onTimeline()));
	connect(ui->btnMentions, SIGNAL(clicked()), this, SLOT(onMentions()));
	connect(ui->btnDirects, SIGNAL(clicked()), this, SLOT(onDirect()));
	connect(&_twitter, SIGNAL(onFriendsTimeline(Timeline *, int)), this, SLOT(onFriendsTimeline(Timeline *, int)));
	connect(&_twitter, SIGNAL(onFriendPicture(QTwitPicture)), this, SLOT(onFriendPicture(QTwitPicture)));
	connect(&_twitter, SIGNAL(onUpdate(Timeline*,int)), this, SLOT(onUpdate(Timeline*,int)));
	connect(&_twitter, SIGNAL(onError(QNetworkReply::NetworkError,QString)), this, SLOT(onError(QNetworkReply::NetworkError,QString)));
	connect(ui->txtUpdate, SIGNAL(submit()), this, SLOT(onUpdatePressed()));
	connect(ui->txtUpdate, SIGNAL(cancel()), this, SLOT(onCancelPressed()));
	_credentials.loadConfig();

	//If proxy
	_twitter.setProxy( CONFIG.getProxyUsername(), CONFIG.getProxyPassword() );
	_twitter.setTwitterAccount( _credentials.getUsername(), _credentials.getPassword() );

	_tipoReq = _TIPO_NADA;
	ui->fraUpdate->setVisible(false);
	_inReplyTo = 0;
	_telaAtual = _TELA_NADA;

	//SYSTRAY ---------------------------------
	_createSystray();

	connect(systray, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
	connect(systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
				 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	systray->setIcon( this->windowIcon() );

	systray->show();
	//=========================================


#ifndef _DISABLE_TIMER
	connect(&timerRefresh, SIGNAL(timeout()), this, SLOT(onRefreshTimeline()));
	timerRefresh.start(60000);
#endif

	rubberBand = NULL;

}

WndTimeline::~WndTimeline()
{
	delete ui;
}

void WndTimeline::mousePressEvent(QMouseEvent *event)
 {
	/*
	 _origin = event->pos();
	 if (!rubberBand)
		 rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
	 rubberBand->setGeometry(QRect(_origin, QSize()));
	 rubberBand->show();
	 qDebug() << "ini rubber";
*/
 }

 void WndTimeline::mouseMoveEvent(QMouseEvent *event)
 {
	 /*
	 if( rubberBand != NULL )
		 rubberBand->setGeometry(QRect(_origin, event->pos()).normalized());
	 */
 }

 void WndTimeline::mouseReleaseEvent(QMouseEvent *event)
 {
	 /*
	 if( rubberBand != NULL )
		 rubberBand->hide();
	 // determine selection, for example using QRect::intersects()
	 // and QRect::contains().
	 */
 }

void WndTimeline::_createSystray()
{
	systray = new QSystemTrayIcon(this);

	actShowHide = new QAction(tr("Show/Hide"), this);
	connect(actShowHide, SIGNAL(triggered()), this, SLOT(onActionShowHideTriggered()));
	actExit = new QAction(tr("Sair"), this);
	connect(actExit, SIGNAL(triggered()), this, SLOT(onActionSairTriggered()));

	trayMenu = new QMenu();
	trayMenu->addAction(actShowHide);
	trayMenu->addSeparator();
	trayMenu->addAction(actExit);

	systray->setContextMenu(trayMenu);
}

void WndTimeline::messageClicked()
{
	QMessageBox::information(0, tr("Systray"),
							 tr("Sorry, I already gave what help I could.\n"
								"Maybe you should try asking a human?"));
}

void WndTimeline::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
	 switch (reason) {
	 case QSystemTrayIcon::Trigger:
		 break;
	 case QSystemTrayIcon::DoubleClick:
		 onActionShowHideTriggered();
		 break;
	 case QSystemTrayIcon::MiddleClick:
		 //showMessage();
		 break;
	 default:
		 ;
	 }
 }

void WndTimeline::_checkMsgList()
{
	if( _msgList.size() < MSG_COUNT ) {
		for(int i= _msgList.size(); i < MSG_COUNT; i++) {
			_msgList.append("");
		}
	}
}

void WndTimeline::onTimeline()
{
	if( !_checkCredentials() ) return;
	_tipoReq = _TIPO_TIMELINE;
	_telaAtual = _TELA_TIMELINE;
	_setWaiting(true);
	_checkMsgList();
	_twitter.getFriendsTimeline(MSG_COUNT);
}

void WndTimeline::onMentions()
{
	if( !_checkCredentials() ) return;
	_tipoReq = _TIPO_TIMELINE;
	_telaAtual = _TELA_MENTIONS;
	_setWaiting(true);
	_checkMsgList();
	_twitter.getMentionsTimeline(MSG_COUNT);
}

void WndTimeline::onDirect()
{
	if( !_checkCredentials() ) return;
	_tipoReq = _TIPO_DIRECT;
	_telaAtual = _TELA_DIRECT;
	_setWaiting(true);
	_checkMsgList();
	_twitter.getDirectsTimeline(MSG_COUNT);
}

void WndTimeline::_setWaiting(bool waiting)
{
	if( waiting ) {
		ui->statusBar->showMessage("Pegando mensagens");
		//ui->scrTimeline->setEnabled(false);
	} else {
		ui->statusBar->clearMessage();
		//ui->scrTimeline->setEnabled(true);
	}
}

void WndTimeline::onFriendsTimeline(Timeline *timeline, int error)
{
	if( error != 0 ) {
		return;
	}

	for(int i=0; i < timeline->getCount(); i++) {
		const QString &text = timeline->getParam(i, "text");
		const QString &user = timeline->getParam(i,_tipoReq==_TIPO_TIMELINE?"user_screen_name":"sender_screen_name");
		const QString &id = timeline->getParam(i,"id");
		const QString &picUrl = timeline->getParam(i,_tipoReq==_TIPO_TIMELINE?"user_profile_image_url":"sender_profile_image_url");

		if( (i+1) > _frameList.size() ) {
			_createItem(i, id, user, picUrl, text, *timeline);
		} else {
			_updateItem(i, id, user, picUrl, text, *timeline);
		}

		//Setting text to RT
		_msgList[i] = user + " " + text;


	}
	_setWaiting(false);
}

void WndTimeline::_createItem(int pos, const QString &id, const QString &user, const QString &picUrl, const QString &text, const Timeline &timeline)
{

	if( ui->scrTimelineContents->layout() == NULL ) {
		QVBoxLayout *lay = new QVBoxLayout();
		lay->setMargin(0);
		lay->setSpacing(2);
		ui->scrTimelineContents->setLayout( lay );

	}

	QVBoxLayout *layScr = (QVBoxLayout *)ui->scrTimelineContents->layout();

	QHBoxLayout *layLine = new QHBoxLayout();

	QLabel *lblText = new QLabel(ui->scrTimelineContents);
	lblText->setObjectName(QString::fromUtf8("lblText"));
	lblText->setWordWrap(true);

	QString itemText = "<a href=\"@" + user + "\"><font color='green'>" + user + "</font></a> ";
	itemText.append( _changeLinks(text) );
	itemText.append("<BR>");
	itemText.append("<a href=\"@@" + id + "|" + user);
	itemText.append("\">Reply</a> - <a href=\"##" + QString::number(pos) + "\">Retweet</a> - ");
	QString msgDate = timeline.getParam(pos, "created_at");
	QDateTime dt = QDateTime::fromString( Timeline::cleanDateTime(msgDate), "MM dd HH:mm:ss yyyy" );
	dt.setTimeSpec( Qt::UTC );
	QDateTime dt_local = dt.toLocalTime();

	QDateTime now = QDateTime::currentDateTime();
	if( dt_local.daysTo( now ) > 1 ) {
		itemText.append(" " + dt_local.toString("dd/MM/yyyy") );
	} else {
		itemText.append(" " + dt_local.toString("HH:mm:ss") );
	}
	itemText.append(" - From: " + timeline.getParam(pos, "source"));

	lblText->setText(itemText);
	lblText->setMaximumWidth( ui->scrTimeline->width() - 52 );
	connect(lblText, SIGNAL(linkActivated(QString)), this, SLOT(linkClicked(QString)));

	QLabel *lblImg = new QLabel(ui->scrTimelineContents);
	lblImg->setObjectName(QString::fromUtf8("lblImg"));
	lblImg->setMinimumSize(QSize(48, 48));
	lblImg->setMaximumSize(QSize(48, 48));
	lblImg->setToolTip(user);
	const QImage *img = _getPicture(user, picUrl);
	if( img != NULL ) {
		lblImg->setPixmap( QPixmap::fromImage(*img) );
	}

	layLine->addWidget(lblImg); //, 0, Qt::AlignLeft);
	layLine->addWidget(lblText, 1);

	QSpacerItem *sp = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding);
	layLine->addItem(sp);

	layScr->addLayout( layLine );

	//Line ---------------------------------------------------------
	QFrame *line = new QFrame(ui->scrTimelineContents);
	line->setObjectName(QString::fromUtf8("line"));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Plain);

	layScr->addWidget( line );

	_frameList.append( FrameItem(lblImg, lblText) );
}

void WndTimeline::_updateItem(int pos, const QString &id, const QString &user, const QString &picUrl, const QString &text, const Timeline &timeline)
{
	if( pos >= _frameList.size() ) {
		QMessageBox::critical(this, "ERRO!!!", "Update chamado para frame > _frameList.size()");
		return;
	}

	const FrameItem &item = _frameList.at(pos);
	QLabel *lblImg = item.first;
	QLabel *lblText = item.second;

	const QImage *img =_getPicture(user, picUrl);
	if( img != NULL ) {
		lblImg->setPixmap( QPixmap::fromImage(*img) );
		lblImg->setToolTip(user);
	}

	QString itemText = "<a href=\"@" + user + "\"><font color='green'>" + user + "</font></a> ";
	itemText.append( _changeLinks(text) );
	itemText.append("<BR>");
	itemText.append("<a href=\"@@" + id + "|" + user);
	itemText.append("\">Reply</a> - <a href=\"##" + QString::number(pos) + "\">Retweet</a> - ");
	QString msgDate = timeline.getParam(pos, "created_at");
	QDateTime dt = QDateTime::fromString( Timeline::cleanDateTime(msgDate), "MM dd HH:mm:ss yyyy" );
	dt.setTimeSpec( Qt::UTC );
	QDateTime dt_local = dt.toLocalTime();

	QDateTime now = QDateTime::currentDateTime();
	if( dt_local.daysTo( now ) > 1 ) {
		itemText.append(" " + dt_local.toString("dd/MM/yyyy") );
	} else {
		itemText.append(" " + dt_local.toString("HH:mm:ss") );
	}
	itemText.append(" - From: " + timeline.getParam(pos, "source"));

	lblText->setText(itemText);

}

QString WndTimeline::_getItem(int pos)
{
	/*
	QFrame *fra = _frameList.at(pos);
	const QObjectList &list = fra->children();

	for( QObjectList::const_iterator it = list.constBegin(); it != list.constEnd(); it++ ) {
		QObject* obj = *it;
		if( obj->objectName() == "lblText" ) {
			QLabel *lbl = (QLabel *)obj;
			return lbl->text();
		}
	}
	*/
	return "";
}

const QImage *WndTimeline::_getPicture(const QString &user, const QString &picUrl)
{
	return _twitter.getPicture(user, picUrl);
}

void WndTimeline::linkClicked(QString desc)
{
	QString ret;

	if( desc.startsWith("@@") ) {
		//Reply message
		ret = _parseReply(desc);
	} else if( desc.startsWith("@") ) {
		//reply to user
		ret = _parseReply(desc);
	} else if( desc.startsWith("http://") ) {
		//Url - Web Browser
		QDesktopServices::openUrl(desc);
	} else if( desc.startsWith("##") ) {
		ret = _parseRT(desc);
	} else if( desc.startsWith("#") ) {
		_parseTag(desc);
	} else {
		QMessageBox::information(this, "link", desc);
	}

	if( ret.size() > 0 ) {
		_showUpdate();
		ui->txtUpdate->setPlainText(ret);
		QTextCursor cursor = ui->txtUpdate->textCursor();
		cursor.setPosition(ret.size());
		ui->txtUpdate->setTextCursor(cursor);
	}

}

QString WndTimeline::_parseReply(const QString &cmd)
{
	QStringList ret;

	if( cmd.startsWith("@@") ) {
		QStringList params = cmd.split("|");
		if( params.size() != 2 ) {
			QMessageBox::critical(this, "Erro", "Erro em reply");
			return "";
		}

		int id=0;
		const QString &sId = params[0];
		if( sId.size() > 2 ) {
			QString s = sId.mid(2);
			id = s.toInt();
		}

		if( params[1].size() > 0 ) {
			ret << "@" << params[1] << " ";

			if( id > 0 ) _inReplyTo = id;
		}

		return ret.join("");
	} else if( cmd.startsWith("@") ) {
		//Simple reply
		_inReplyTo = 0;
		return cmd + " ";
	}
	return "";

}

void WndTimeline::_parseTag(const QString &tag)
{
	QUrl url("http://search.twitter.com/search");

	QPair<QString, QString> item;
	item.first = "q";
	item.second = tag;
	QList<QPair<QString, QString> > list;
	list.append(item);

	url.setQueryItems(list);

	QDesktopServices::openUrl(url);
}

QString WndTimeline::_parseRT(const QString &msgNum)
{
	int msg;
	if( !msgNum.startsWith("##") ) {
		return "";
	}
	msg = msgNum.mid(2).toInt();

	return "RT @" + _msgList[msg];

}

QString WndTimeline::_changeLinks(const QString &text)
{
	QString ret;
	int ini = 0;
	int end = 0;

	while( ini != -1 ) {
		ini = text.indexOf("http://", end);
		int ini1 = text.indexOf("@", end);
		int ini2 = text.indexOf("#", end);
		if( ini1 != -1 || ini2 != -1 ) {
			int first = ini1;
			if( (ini2 != -1 && ini2 < ini1) || ini1 == -1 ) first = ini2;
			if( first != -1 && first+1 <= text.size() ) {
				if( !text.at(first+1).isLetterOrNumber() )
					first = -1;
			}
			ini1 = first;
		}

		if( (ini1 != -1 && ini1 < ini) || ini == -1 ) ini = ini1;

		if( ini != -1 ) {
			if( ini > 0 ) ret += text.mid(end, ini-end);
			end = _endTok(text, ini);
			QString link = text.mid(ini, end-ini);
			link = _cleanLink(link);
			ret += "<a href=\"" + link + "\">" + link + "</a>";
		}
	}

	if( ini != text.size() && end != -1 ) {
		ret += text.mid(end);
	}
	return ret;
}

int WndTimeline::_endTok(const QString &text, int pos)
{
	int i;
	for(i=pos; i < text.size(); i++) {
		QChar c = text.at(i);
		if( !(c.isLetterOrNumber() || c == '/' || c == ':' || c == '?' || c == '=' ||
			  c == '&' || c == '-' || c == '_' || c == '.' || c == '@' || c == '#' || c == ',') ) {
			return i;
		}
	}
	return i;
}

QString WndTimeline::_cleanLink(const QString &tok)
{
	if( tok.startsWith("@") || tok.startsWith("#") ) {
		int i=0;
		//Let's skip @, #
		for(;i < tok.size(); i++) {
			QChar c = tok.at(i);
			if( c.isLetterOrNumber() || c == '_' || c == '.' ) break;
		}

		//Let's get the last alphanumeric
		for(;i < tok.size(); i++) {
			QChar c = tok.at(i);
			if( !(c.isLetterOrNumber() || c == '_' || c == '.') ) {
				break;
			}
		}
		if( i > 0 ) {
			QString ret = tok.left(i);
			if( ret.endsWith(".") ) {
				ret = ret.left(ret.size() - 1);
			}
			return ret;
		}
	}
	return tok;
}

bool WndTimeline::_checkCredentials()
{
	if( !_credentials.hasUserSet() ) {
		QMessageBox::critical(this, tr("Erro logando"), tr("O usu&aacute;rio e senha do twitter<BR>n&atilde;o est&atilde;o configurados."));
		return false;
	}
	return true;
}

void WndTimeline::onFriendPicture(const QTwitPicture &pic)
{
	//qDebug() << "CHEGOU IMG " << pic.getUsername();
	QList< QPair<QLabel *, QLabel *> >::iterator itf = _frameList.begin();

	for(; itf != _frameList.end(); itf++) {
		QLabel *lblImg = itf->first;
		QLabel *lblText = itf->second;

		if( lblImg->objectName() == "lblImg" ) {
			QString user = (QString)lblImg->toolTip();
			if( user == pic.getUsername() ) {
				lblImg->setPixmap( QPixmap::fromImage(pic) );
			}
		}
	}//framelist
}

void WndTimeline::on_actionConfigurar_triggered()
{
	FrmConfig cfg(this);
        cfg.setWindowFlags(cfg.windowFlags() | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	cfg.setModal(true);
	cfg.exec();
	_credentials.loadConfig();
	_twitter.setTwitterAccount( _credentials.getUsername(), _credentials.getPassword() );
}

void WndTimeline::onActionSairTriggered()
{
	this->close();
}

void WndTimeline::onActionShowHideTriggered()
{
	if( this->isHidden() ) {
		this->show();
	} else {
		this->hide();
	}
}

void WndTimeline::on_actionUpdate_triggered()
{
	if( ui->fraUpdate->isVisible() ) {
		ui->fraUpdate->setVisible(false);
	} else {
		_showUpdate();
	}
}

void WndTimeline::_showUpdate()
{
	ui->fraUpdate->setVisible(true);
	ui->lblCount->setText("0");
	ui->txtUpdate->setFocus();
}

void WndTimeline::onUpdatePressed()
{
	if( ui->txtUpdate->toPlainText().size() <= 140 ) {
		QString text = ui->txtUpdate->toPlainText();
		if( text.size() > 0 ) {
			ui->txtUpdate->setEnabled(false);
			_twitter.postUpdate( text, _inReplyTo );
			_inReplyTo = 0;
		}
	} else {
		QMessageBox::critical(this, "Erro!", "O tamanho total da mensagem é de 140 caracteres");
	}
}

void WndTimeline::onCancelPressed()
{
	ui->txtUpdate->clear();
	ui->fraUpdate->setVisible(false);
}

void WndTimeline::onUpdate(Timeline *timeLine, int error)
{
	ui->txtUpdate->clear();
	ui->statusBar->showMessage("Update feito com sucesso!", 2000);
	ui->txtUpdate->setEnabled(true);
	ui->fraUpdate->setVisible(false);

	onRefreshTimeline();
}

void WndTimeline::onError(QNetworkReply::NetworkError error, const QString &errorString)
{
	ui->statusBar->showMessage(errorString);
	//FrmNotification::showMessage(errorString);
}

void WndTimeline::on_txtUpdate_textChanged()
{
	int tam = ui->txtUpdate->toPlainText().size();
	if( tam > 140 ) {
		ui->lblCount->setStyleSheet("color:red;");
	} else {
		ui->lblCount->setStyleSheet("");
	}
	ui->lblCount->setText( QString::number(tam) );
}

void WndTimeline::onRefreshTimeline()
{
	switch( _telaAtual ) {
	case _TELA_TIMELINE:
		onTimeline();
		break;
	case _TELA_MENTIONS:
		onMentions();
		break;
	case _TELA_DIRECT:
		onDirect();
		break;
	}
}
