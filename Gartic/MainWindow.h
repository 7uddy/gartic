#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "LoginPage.h"
#include "RegisterPage.h"
#include "MainMenuPage.h"
#include "PageController.h"
#include "ProfilePage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Show();
    void SetBackground();
private:
    Ui::MainWindowClass ui;
    LoginPage* loginPage;
    RegisterPage* registerPage;
    PageController* pageController;
    MainMenuPage* mainMenuPage;
    ProfilePage* profilePage;
};
