/********************************************************************************
** Form generated from reading ui file 'wndtimeline.ui'
**
** Created: Wed 18. Nov 12:58:05 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_WNDTIMELINE_H
#define UI_WNDTIMELINE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WndTimeline
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnTimeline;
    QPushButton *btnMentions;
    QPushButton *btnDirects;
    QScrollArea *scrTimeline;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *layTimeline;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WndTimeline)
    {
        if (WndTimeline->objectName().isEmpty())
            WndTimeline->setObjectName(QString::fromUtf8("WndTimeline"));
        WndTimeline->resize(378, 454);
        WndTimeline->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(WndTimeline);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnTimeline = new QPushButton(centralWidget);
        btnTimeline->setObjectName(QString::fromUtf8("btnTimeline"));
        btnTimeline->setCursor(QCursor(Qt::PointingHandCursor));
        btnTimeline->setStyleSheet(QString::fromUtf8("color:#050; \n"
"background-color:#fed; \n"
"border:1px solid; \n"
"border-color: #696 #363 #363 #696;"));

        horizontalLayout->addWidget(btnTimeline);

        btnMentions = new QPushButton(centralWidget);
        btnMentions->setObjectName(QString::fromUtf8("btnMentions"));
        btnMentions->setCursor(QCursor(Qt::PointingHandCursor));
        btnMentions->setStyleSheet(QString::fromUtf8("color:#050; \n"
"background-color:#fed; \n"
"border:1px solid; \n"
"border-color: #696 #363 #363 #696;"));

        horizontalLayout->addWidget(btnMentions);

        btnDirects = new QPushButton(centralWidget);
        btnDirects->setObjectName(QString::fromUtf8("btnDirects"));
        btnDirects->setCursor(QCursor(Qt::PointingHandCursor));
        btnDirects->setStyleSheet(QString::fromUtf8("color:#050; \n"
"background-color:#fed; \n"
"border:1px solid; \n"
"border-color: #696 #363 #363 #696;"));

        horizontalLayout->addWidget(btnDirects);


        verticalLayout->addLayout(horizontalLayout);

        scrTimeline = new QScrollArea(centralWidget);
        scrTimeline->setObjectName(QString::fromUtf8("scrTimeline"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrTimeline->sizePolicy().hasHeightForWidth());
        scrTimeline->setSizePolicy(sizePolicy);
        scrTimeline->setMinimumSize(QSize(0, 0));
        scrTimeline->setAutoFillBackground(false);
        scrTimeline->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrTimeline->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 358, 355));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setMargin(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        layTimeline = new QVBoxLayout();
        layTimeline->setSpacing(0);
        layTimeline->setObjectName(QString::fromUtf8("layTimeline"));
        layTimeline->setSizeConstraint(QLayout::SetMaximumSize);

        horizontalLayout_2->addLayout(layTimeline);

        scrTimeline->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrTimeline);

        WndTimeline->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WndTimeline);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 378, 22));
        WndTimeline->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WndTimeline);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        WndTimeline->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WndTimeline);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        WndTimeline->setStatusBar(statusBar);

        retranslateUi(WndTimeline);

        QMetaObject::connectSlotsByName(WndTimeline);
    } // setupUi

    void retranslateUi(QMainWindow *WndTimeline)
    {
        WndTimeline->setWindowTitle(QApplication::translate("WndTimeline", "WndTimeline", 0, QApplication::UnicodeUTF8));
        btnTimeline->setText(QApplication::translate("WndTimeline", "&Friends", 0, QApplication::UnicodeUTF8));
        btnTimeline->setShortcut(QApplication::translate("WndTimeline", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        btnMentions->setText(QApplication::translate("WndTimeline", "&Mentions", 0, QApplication::UnicodeUTF8));
        btnMentions->setShortcut(QApplication::translate("WndTimeline", "Ctrl+M", 0, QApplication::UnicodeUTF8));
        btnDirects->setText(QApplication::translate("WndTimeline", "&Directs", 0, QApplication::UnicodeUTF8));
        btnDirects->setShortcut(QApplication::translate("WndTimeline", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(WndTimeline);
    } // retranslateUi

};

namespace Ui {
    class WndTimeline: public Ui_WndTimeline {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDTIMELINE_H
