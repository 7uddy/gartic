#pragma once
#include <QtWidgets>
#include "PageController.h"

class LoginPage : public QWidget
{
	Q_OBJECT
public:
	LoginPage(PageController* controller,QWidget* parent = nullptr);
	void PlaceElements();
	void LoginButtonClicked();
private:
	QPushButton* loginButton;
	QPushButton* registerButton;
	QLineEdit* username;
	QLineEdit* password;
};

