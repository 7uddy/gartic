#pragma once
#include <QtWidgets>
#include "PageController.h"

class RegisterPage : public QWidget
{
	Q_OBJECT
public:
	RegisterPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void RegisterButtonClicked();
private:
	QPushButton* loginButton;
	QPushButton* registerButton;
	QLineEdit* username;
	QLineEdit* email;
	QLineEdit* password;
};

