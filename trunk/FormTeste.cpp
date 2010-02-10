#include "FormTeste.h"
#include "ui_FormTeste.h"

FormTeste::FormTeste(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTeste)
{
    ui->setupUi(this);
}

FormTeste::~FormTeste()
{
    delete ui;
}

void FormTeste::changeEvent(QEvent *e)
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
