#include <QtGui/QApplication>
#include "wndtimeline.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WndTimeline w;
    w.show();
    return a.exec();
}
