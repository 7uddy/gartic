#include "LoginPage.h"

LoginPage::LoginPage(PageController* controller,QWidget* parent)
{
	loginButton = new QPushButton("Login", this);
	registerButton = new QPushButton("Don't have an account? Signup", this);
	username = new QLineEdit(this);
	password = new QLineEdit(this);
	imageLabel = new QLabel(this);
    layout = new QVBoxLayout(this);
	SetSize();
	StyleElements();
	PlaceElements();
	connect(loginButton, &QPushButton::clicked, this, &LoginPage::LoginButtonClicked);
	connect(registerButton, &QPushButton::clicked, controller, [controller]() {
		controller->showPage("Register");
		});
}

void LoginPage::PlaceElements()
{
	setLayout(layout);

	QHBoxLayout* innerLayout = new QHBoxLayout;
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	innerLayout->addWidget(imageLabel);
	innerLayout->setContentsMargins(55,0, 0,70);

	layout->setContentsMargins(400,100,400,100);
	layout->addLayout(innerLayout);
	layout->addWidget(username);
	layout->addWidget(password);
	layout->addWidget(loginButton);
	layout->addWidget(registerButton);
	layout->setAlignment(Qt::AlignCenter);
}

void LoginPage::StyleElements()
{
	password->setEchoMode(QLineEdit::Password);
	username->setPlaceholderText("Username");
	password->setPlaceholderText("Password");
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void LoginPage::SetSize()
{
	username->setFixedSize(400, 50);
	password->setFixedSize(400, 50);
	loginButton->setFixedSize(400, 50);
	registerButton->setFixedSize(400, 50);
	username->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	password->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	loginButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	registerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void LoginPage::LoginButtonClicked()
{

}


