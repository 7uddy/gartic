#pragma once
#include <QtWidgets>
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
	~LoginPage();
private:
	QPushButton* loginButton,* registerButton;
	QLineEdit* username,* password;
	QVBoxLayout* layout;
	QHBoxLayout* innerLayout;
	QLabel* imageLabel;
};

