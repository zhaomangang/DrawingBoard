#include "drawwidget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawWidget w;
    w.setWindowIcon(QIcon(":/image/tb.png"));
    w.show();

    return a.exec();
}
