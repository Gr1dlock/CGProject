#include "interface/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    unsigned char A = 200;
    unsigned char B = 100;
    unsigned char C = std::min(255, A*B);
    qDebug() << B - A;
    w.show();
    return a.exec();
}
