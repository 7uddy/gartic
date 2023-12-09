#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QMessageBox>
#include "../DLL/DLL/Player.h"

class PageController:public QStackedWidget
{
public:
	PageController(QWidget* parent = nullptr);
	void AddPage(QWidget *page, const QString& name);
	void ShowPage(const QString& name);
	void SetStartupPage(const QString& name);
	bool VerifyLogin(const QString& enteredUsername, const QString& enteredPassword);
	bool VerifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword);
private:
	QMap<QString, QWidget*> pagesMap;
	Player player;
};

