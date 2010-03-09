#include "FrmNotification.h"
#include "ui_FrmNotification.h"

#include <QDesktopWidget>
#include <QTimer>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QDebug>

FrmNotification::FrmNotification(QWidget *parent) :
		QWidget(parent, Qt::FramelessWindowHint),
    ui(new Ui::FrmNotification)
{
    ui->setupUi(this);
	Qt::WindowFlags flags = this->windowFlags();
	flags |= Qt::WindowStaysOnTopHint;
	this->setWindowFlags(flags);
}

FrmNotification::~FrmNotification()
{
    delete ui;
}

FrmNotification &FrmNotification::getInstance()
{
	static FrmNotification me;
	return me;
}

void FrmNotification::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FrmNotification::showEvent(QShowEvent *)
{
	QTimer::singleShot(2000, this, SLOT(closeMe()));
}

void FrmNotification::showMessage(const QString &msg)
{
	FrmNotification &frm = getInstance();
	if( frm.isHidden() ) {
		QDesktopWidget *desk = qApp->desktop();
		QRect rect = desk->availableGeometry();
		frm.move( rect.width() - frm.width(), rect.height() - frm.height() );

		frm.ui->lblMsg->setText(msg);
		frm.show();
	}
}

void FrmNotification::closeMe()
{
	qDebug() << "closeMe";
	this->hide();
	/*
	QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
	animation->setStartValue( this->rect() );
	QRect rec = this->rect();
	rec.setTop( rec.top() + rec.height() );
	animation->setEndValue( rec );
	animation->setDuration(1000);
	animation->setEasingCurve(QEasingCurve::InOutQuad);
	animation->start(QAbstractAnimation::DeleteWhenStopped);

	connect(animation, SIGNAL(finished()), this, SLOT(hide()));
	*/
}
