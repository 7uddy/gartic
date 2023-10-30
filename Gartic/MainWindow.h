#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "LoginPage.h"
#include "RegisterPage.h"
#include "PageController.h"

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
    LoginPage* loginpage;
    RegisterPage* registerpage;
    PageController* pageController;
};
