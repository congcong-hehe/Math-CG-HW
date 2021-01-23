#include "ImageWarp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageWarp w;
    w.show();
    return a.exec();
}
