#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Gartic");
    pageController = new PageController(this);
    loginPage = new LoginPage(pageController);
    registerPage = new RegisterPage(pageController);
    mainMenuPage = new MainMenuPage(pageController);
    profilePage = new ProfilePage(pageController);
    waitingRoomPage = new WaitingRoomPage(pageController);
    selectRoomPage = new SelectRoomPage(pageController);
    gamePage = new GamePage(pageController);
    leaderboardPage = new LeaderboardPage(pageController);
    AddPages();
    setCentralWidget(pageController);
    SetBackground();
    setGeometry(100, 100, 1200, 800);
    QIcon appIcon("Images/App_icon.ico");
    setWindowIcon(appIcon);
}

MainWindow::~MainWindow()
{
    delete loginPage, registerPage, pageController, mainMenuPage, profilePage, waitingRoomPage, selectRoomPage, gamePage, leaderboardPage;
}

void MainWindow::Show()
{
    pageController->SetStartupPage("Login");
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

void MainWindow::AddPages()
{
    pageController->AddPage(loginPage, "Login");
    pageController->AddPage(registerPage, "Register");
    pageController->AddPage(mainMenuPage, "MainMenu");
    pageController->AddPage(profilePage, "Profile");
    pageController->AddPage(waitingRoomPage, "WaitingRoom");
    pageController->AddPage(selectRoomPage, "SelectRoom");
    pageController->AddPage(gamePage, "Game");
    pageController->AddPage(leaderboardPage, "Leaderboard");
}
