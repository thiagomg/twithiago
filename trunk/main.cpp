#include <QtGui/QApplication>
#include "wndtimeline.h"
//#include "FormTeste.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	WndTimeline w;
	//FormTeste w;
    w.show();
    return a.exec();
}
