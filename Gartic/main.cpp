#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

#include "Jucator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
