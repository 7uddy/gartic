#include "RegisterPage.h"

RegisterPage::RegisterPage(PageController* controller, QWidget* parent)
{
	registerButton = new QPushButton("Signup", this);
	loginButton = new QPushButton("Already have an account? Login", this);
	username = new QLineEdit(this);
	email = new QLineEdit(this);
	password = new QLineEdit(this);
	password->setEchoMode(QLineEdit::Password);
	username->setPlaceholderText("Username");
	email->setPlaceholderText("Email");
	password->setPlaceholderText("Password");
	PlaceElements();
	connect(loginButton, &QPushButton::clicked, controller, [controller]() {
		controller->showPage("Login");
		});
	connect(registerButton, &QPushButton::clicked, this, &RegisterPage::RegisterButtonClicked);
}

void RegisterPage::PlaceElements()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	setLayout(layout);
	layout->addWidget(username);
	layout->addWidget(email);
	layout->addWidget(password);
	layout->addWidget(registerButton);
	layout->addWidget(loginButton);
	layout->setAlignment(Qt::AlignTop);
}

void RegisterPage::RegisterButtonClicked()
{
}
