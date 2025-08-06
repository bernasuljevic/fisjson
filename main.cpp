#include <QApplication>
#include "printwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrintWidget w;
    w.show();
    return a.exec();
}
