#include "LoginPage.h"

LoginPage::LoginPage(PageController* controller,QWidget* parent)
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
	connect(registerButton, &QPushButton::clicked, controller, [controller]() {
		controller->showPage("Register");
		});
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


