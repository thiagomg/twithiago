#include "frmconfig.h"
#include "ui_frmconfig.h"

#include "Config.h"

#include <QCloseEvent>

FrmConfig::FrmConfig(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FrmConfig)
{
    m_ui->setupUi(this);

	m_ui->lnePassword->setEchoMode( QLineEdit::Password );
	m_ui->lneProxyPassword->setEchoMode( QLineEdit::Password );

	m_ui->lneUser->setText( CONFIG.getUsername() );
	m_ui->lnePassword->setText( CONFIG.getPassword() );
	m_ui->lneProxyUser->setText( CONFIG.getProxyUsername() );
	m_ui->lneProxyPassword->setText( CONFIG.getProxyPassword() );
}

FrmConfig::~FrmConfig()
{
    delete m_ui;
}

void FrmConfig::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FrmConfig::closeEvent(QCloseEvent * event)
{
	CONFIG.setUsername(m_ui->lneUser->text());
	CONFIG.setPassword(m_ui->lnePassword->text());
	CONFIG.setProxyUsername(m_ui->lneProxyUser->text());
	CONFIG.setProxyPassword(m_ui->lneProxyPassword->text());

	event->accept();
}
