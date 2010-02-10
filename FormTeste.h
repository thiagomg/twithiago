#ifndef FORMTESTE_H
#define FORMTESTE_H

#include <QWidget>

namespace Ui {
    class FormTeste;
}

class FormTeste : public QWidget {
    Q_OBJECT
public:
    FormTeste(QWidget *parent = 0);
    ~FormTeste();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FormTeste *ui;
};

#endif // FORMTESTE_H
