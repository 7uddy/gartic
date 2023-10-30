#pragma once
#include <QtWidgets>
#include <QPalette>
#include "PageController.h"

class LoginPage : public QWidget
{
	Q_OBJECT
public:
	LoginPage(PageController* controller,QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	void LoginButtonClicked();
private:
	QPushButton* loginButton;
	QPushButton* registerButton;
	QLineEdit* username;
	QLineEdit* password;
	QVBoxLayout* layout;
	QLabel* imageLabel;
};

