#pragma once
#include <QtWidgets>

class LoginPage : public QWidget
{
	Q_OBJECT
public:
	LoginPage(QWidget* parent = nullptr);
	void PlaceElements();
	void LoginButtonClicked();
	void RegisterButtonClicked();
private:
	QPushButton* loginButton;
	QPushButton* registerButton;
	QLineEdit* username;
	QLineEdit* password;
};

