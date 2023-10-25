#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Gartic");
    loginpage = new LoginPage;
    pageController = new PageController(this);
    pageController->addPage(loginpage);
    setCentralWidget(pageController);
}

MainWindow::~MainWindow()
{}
