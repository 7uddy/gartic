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
    SetBackground();
    setGeometry(100, 100, 1200, 800);
}

MainWindow::~MainWindow()
{}

void MainWindow::Show()
{
    pageController->setStartupPage("Login");
    QMainWindow::show();
}

void MainWindow::SetBackground()
{
    QString imageUrl = "Images/Background_game.jpg";
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QImage(imageUrl)));
    this->setPalette(palette);
}
