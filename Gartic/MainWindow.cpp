#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Gartic");
    loginpage = new LoginPage;
    registerpage = new RegisterPage;
    pageController = new PageController(this);
    pageController->addPage(registerpage);
    setCentralWidget(pageController);
}

MainWindow::~MainWindow()
{}
