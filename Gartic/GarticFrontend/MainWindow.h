#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "LoginPage.h"
#include "RegisterPage.h"
#include "MainMenuPage.h"
#include "PageController.h"
#include "ProfilePage.h"
#include "WaitingRoomPage.h"
#include "SelectRoomPage.h"
#include "GamePage.h"
#include "LeaderboardPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Show();
    void SetBackground();
    void AddPages();
private:
    Ui::MainWindowClass ui;
    LoginPage* loginPage;
    RegisterPage* registerPage;
    PageController* pageController;
    MainMenuPage* mainMenuPage;
    ProfilePage* profilePage;
    WaitingRoomPage* waitingRoomPage;
    SelectRoomPage* selectRoomPage;
    GamePage* gamePage;
    LeaderboardPage* leaderboardPage;
};
