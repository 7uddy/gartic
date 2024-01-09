#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QMessageBox>
#include <string>
#include "../DLL/DLL/Player.h"

class PageController:public QStackedWidget
{
public:
	PageController(QWidget* parent = nullptr);
	// PAGE MECHANISM
	void AddPage(QWidget *page, const QString& name);
	void ShowPage(const QString& name);
	void SetStartupPage(const QString& name);
	// VERIFIES LOGIN/REGISTER
	bool VerifyLogin(const QString& enteredUsername, const QString& enteredPassword);
	bool VerifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword);
	// FUNCTIONS RELATED TO THE SERVER CONNECTION
	bool CreateRoom();
	bool VerifyCode(const QString& enteredCode);
	bool LeaveRoom();
	// GETTERS 
	std::string GetLobbyCode();
	Player GetPlayer();
private:
	QMap<QString, QWidget*> pagesMap;
	Player player;
	std::string roomCode;
};

