#pragma once
#include <QtWidgets>
#include <QFile>
#include "PageController.h"

class RegisterPage : public QWidget
{
	Q_OBJECT
public:
	RegisterPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	void RegisterButtonClicked();
	~RegisterPage();
private:
	QPushButton* loginButton, * registerButton;
	QLineEdit* username,* email,* password;
	QVBoxLayout* layout;
	QHBoxLayout* innerLayout;
	QLabel* imageLabel;
};

