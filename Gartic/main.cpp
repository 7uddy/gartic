#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

#include "Jucator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Added console interface
    AllocConsole();
    if(!freopen("CONIN$", "r", stdin))
        throw(std::exception("input flux not open."));
    if (!freopen("CONOUT$", "w", stdout))
        throw(std::exception("output flux not open."));
    QTextStream input(stdin);
    QTextStream output(stdout);
    //Added console interface
    return a.exec();
}
