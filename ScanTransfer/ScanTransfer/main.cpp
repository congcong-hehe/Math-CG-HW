#include "ScanTransfer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScanTransfer w;
    w.show();
    return a.exec();
}
