/********************************************************************************
** Form generated from reading UI file 'FormTeste.ui'
**
** Created: Tue 9. Feb 13:10:29 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTESTE_H
#define UI_FORMTESTE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTeste
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *mainLay;
    QHBoxLayout *lineLay;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *FormTeste)
    {
        if (FormTeste->objectName().isEmpty())
            FormTeste->setObjectName(QString::fromUtf8("FormTeste"));
        FormTeste->resize(316, 126);
        verticalLayout_2 = new QVBoxLayout(FormTeste);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        mainLay = new QVBoxLayout();
        mainLay->setObjectName(QString::fromUtf8("mainLay"));
        lineLay = new QHBoxLayout();
        lineLay->setObjectName(QString::fromUtf8("lineLay"));
        label_2 = new QLabel(FormTeste);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(48, 48));
        label_2->setMaximumSize(QSize(48, 48));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/imgs/catapult_g")));

        lineLay->addWidget(label_2);

        label = new QLabel(FormTeste);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        lineLay->addWidget(label);


        mainLay->addLayout(lineLay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(FormTeste);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(48, 48));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/imgs/catapult_g")));

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(FormTeste);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        horizontalLayout->addWidget(label_4);


        mainLay->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(mainLay);


        retranslateUi(FormTeste);

        QMetaObject::connectSlotsByName(FormTeste);
    } // setupUi

    void retranslateUi(QWidget *FormTeste)
    {
        FormTeste->setWindowTitle(QApplication::translate("FormTeste", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label->setText(QApplication::translate("FormTeste", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Lucida Grande,Lucida Sans,Arial,sans-serif'; font-size:8pt; color:#000000;\">Oficial da Mozilla recomenda usu\303\241rios do FF a trocar o search engine padr\303\243o do Google para o Bing </span><a href=\"http://bit.ly/5iAOik\"><span style=\" font-family:'Lucida Grande,Lucida Sans,Arial,sans-serif'; font-size:8pt; text-decoration: underline; color:#666655;\">http://bit.ly/5iAOik</span></a></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        label_4->setText(QApplication::translate("FormTeste", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">You may follow Tatiana Massari as well by clicking on the &quot;follow&quot; button on their profile.If you believe Tatiana Massari is engaging in ddd</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormTeste: public Ui_FormTeste {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTESTE_H
