#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QMessageBox>
#include <string>
#include "../DLL/DLL/Player.h"
#include <cpr/cpr.h>

class PageController:public QStackedWidget
{
public:
	PageController(QWidget* parent = nullptr);
	void AddPage(QWidget *page, const QString& name);
	void ShowPage(const QString& name);
	void SetStartupPage(const QString& name);
	bool VerifyLogin(const QString& enteredUsername, const QString& enteredPassword);
	bool VerifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword);
	bool CreateRoom();
	bool VerifyCode(const QString& enteredCode);
private:
	QMap<QString, QWidget*> pagesMap;
	Player player;
};

