#include "wndtimeline.h"
#include "ui_wndtimeline.h"

#include <QMessageBox>
#include <QLabel>
#include <QCommandLinkButton>

WndTimeline::WndTimeline(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WndTimeline)
{
    ui->setupUi(this);

	connect(ui->btnTimeline, SIGNAL(clicked()), this, SLOT(onTimeline()));
	connect(ui->btnMentions, SIGNAL(clicked()), this, SLOT(onMentions()));
	connect(ui->btnDirects, SIGNAL(clicked()), this, SLOT(onDirect()));
	connect(&_twitter, SIGNAL(onFriendsTimeline(Timeline *, int)), this, SLOT(onFriendsTimeline(Timeline *, int)));

	//If proxy
	_twitter.setProxy("proxy_user", "proxy_pwd");
	_twitter.setTwitterAccount("twitter_user", "twitter_pwd");

	_tipoReq = _TIPO_NADA;

}

WndTimeline::~WndTimeline()
{
	delete ui;
}

void WndTimeline::onTimeline()
{
	_tipoReq = _TIPO_TIMELINE;
	_setWaiting(true);
	_twitter.getFriendsTimeline();
}

void WndTimeline::onMentions()
{
	_tipoReq = _TIPO_TIMELINE;
	_setWaiting(true);
	_twitter.getMentionsTimeline();
}

void WndTimeline::onDirect()
{
	_tipoReq = _TIPO_DIRECT;
	_setWaiting(true);
	_twitter.getDirectsTimeline();
}

void WndTimeline::_setWaiting(bool waiting)
{
	if( waiting ) {
		ui->statusBar->showMessage("Pegando mensagens");
		ui->scrTimeline->setEnabled(false);
	} else {
		ui->statusBar->clearMessage();
		ui->scrTimeline->setEnabled(true);
	}
}

void WndTimeline::onFriendsTimeline(Timeline *timeline, int error)
{
	if( error != 0 ) return;

	for(int i=0; i < timeline->getCount(); i++) {
		const QString &text = timeline->getParam(i, "text");
		const QString &user = timeline->getParam(i,_tipoReq==_TIPO_TIMELINE?"user_screen_name":"sender_screen_name");

		if( (i+1) > _frameList.size() ) {
			QFrame *fra = new QFrame(ui->scrTimeline);
			_frameList.push_back(fra);
			fra->setLayout( new QVBoxLayout() );
			fra->layout()->setMargin(1);
			fra->setStyleSheet("background-color: rgb(234, 255, 234);");
			ui->layTimeline->addWidget( fra );

			//Link ---------------------------------------------------------
			QLabel *link = new QLabel(fra);
			link->setObjectName("lblUser");
			link->setText("<a href=\"@" + user + "\"><font color='green'>" + user + "</font></a> ");
			connect(link, SIGNAL(linkActivated(QString)), this, SLOT(linkClicked(QString)));
			fra->layout()->addWidget(link);

			//Text ---------------------------------------------------------
			QLabel *lbl = new QLabel(ui->scrTimeline);
			lbl->setObjectName("lblText");
			lbl->setText( _changeLinks(text) );
			connect(lbl, SIGNAL(linkActivated(QString)), this, SLOT(linkClicked(QString)));
			lbl->setWordWrap(true);
			fra->layout()->addWidget(lbl);

			//Line ---------------------------------------------------------
			QFrame *line = new QFrame(fra);
			line->setObjectName(QString::fromUtf8("line"));
			line->setFrameShape(QFrame::HLine);
			line->setFrameShadow(QFrame::Plain);
			fra->layout()->addWidget(line);
		} else {
			QFrame *fra = _frameList.at(i);
			const QObjectList &list = fra->children();

			for( QObjectList::const_iterator it = list.constBegin(); it != list.constEnd(); it++ ) {
				QObject* obj = *it;
				if( obj->objectName() == "lblUser" ) {
					QLabel *link = (QLabel *)obj;
					link->setText("* <a href=\"@" + user + "\"><font color='green'>" + user + "</font></a> ");
				} else if( obj->objectName() == "lblText" ) {
					QLabel *lbl = (QLabel *)obj;
					lbl->setText( "# " + _changeLinks(text) );
				}
			}

		}

	}
	_setWaiting(false);
}

void WndTimeline::linkClicked(QString desc)
{
	QMessageBox::information(this, "link", desc);
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
		if( !(c.isLetterOrNumber() || c == '/' || c == ':' || c == '?' ||
			  c == '&' || c == '-' || c == '_' || c == '.' || c == '@' || c == '#' ) ) {
			return i;
		}
	}
	return i;
}
