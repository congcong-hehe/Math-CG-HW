#include "Bresenham.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bresenham w;
    w.show();
    return a.exec();
}
