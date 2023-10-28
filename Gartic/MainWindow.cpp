#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Gartic");
    pageController = new PageController(this);
    loginpage = new LoginPage(pageController);
    registerpage = new RegisterPage(pageController);
    pageController->addPage(loginpage, "Login");
    pageController->addPage(registerpage, "Register");
    setCentralWidget(pageController);
}

MainWindow::~MainWindow()
{}

void MainWindow::show()
{
    pageController->setStartupPage("Login");
    QMainWindow::show();
}
