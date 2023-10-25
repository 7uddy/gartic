#include "LoginPage.h"

LoginPage::LoginPage(QWidget* parent)
{
	loginButton = new QPushButton("Login", this);
	registerButton = new QPushButton("Don't have an account? Signup", this);
	username = new QLineEdit(this);
	password = new QLineEdit(this);
	password->setEchoMode(QLineEdit::Password);
	username->setPlaceholderText("Username");
	password->setPlaceholderText("Password");
	PlaceElements();
	connect(loginButton, &QPushButton::clicked, this, &LoginPage::LoginButtonClicked);
	connect(registerButton, &QPushButton::clicked, this, &LoginPage::RegisterButtonClicked);
}

void LoginPage::PlaceElements()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	setLayout(layout);
	layout->addWidget(username);
	layout->addWidget(password);
	layout->addWidget(loginButton);
	layout->addWidget(registerButton);
	layout->setAlignment(Qt::AlignTop);
}

void LoginPage::LoginButtonClicked()
{

}

void LoginPage::RegisterButtonClicked()
{

}
