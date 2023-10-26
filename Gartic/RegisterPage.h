#pragma once
#include <QtWidgets>

class RegisterPage : public QWidget
{
	Q_OBJECT
public:
	RegisterPage(QWidget* parent = nullptr);
	void PlaceElements();
	void LoginButtonClicked();
	void RegisterButtonClicked();
private:
	QPushButton* loginButton;
	QPushButton* registerButton;
	QLineEdit* username;
	QLineEdit* email;
	QLineEdit* password;
};

