#ifndef FRMNOTIFICATION_H
#define FRMNOTIFICATION_H

#include <QWidget>

namespace Ui {
    class FrmNotification;
}

class FrmNotification : public QWidget {
    Q_OBJECT
private:
    FrmNotification(QWidget *parent = 0);
	static FrmNotification &getInstance();

public:
	~FrmNotification();

	static void showMessage(const QString &msg);

protected:
    void changeEvent(QEvent *e);
	void showEvent(QShowEvent *);

private:
    Ui::FrmNotification *ui;

private slots:
	void closeMe();
};

#endif // FRMNOTIFICATION_H
