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
private:
	QPushButton* loginButton;
	QPushButton* registerButton;
	QLineEdit* username;
	QLineEdit* email;
	QLineEdit* password;
	QVBoxLayout* layout;
	QLabel* imageLabel;
};

