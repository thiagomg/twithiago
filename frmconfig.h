#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QtGui/QDialog>

namespace Ui {
    class FrmConfig;
}

class FrmConfig : public QDialog {
    Q_OBJECT
public:
    FrmConfig(QWidget *parent = 0);
    ~FrmConfig();

protected:
    void changeEvent(QEvent *e);
	void closeEvent(QCloseEvent * event);

private:
    Ui::FrmConfig *m_ui;
};

#endif // FRMCONFIG_H
