#include "RegisterPage.h"

RegisterPage::RegisterPage(PageController* controller, QWidget* parent)
{
	registerButton = new QPushButton("Signup", this);
	loginButton = new QPushButton("Already have an account? Login", this);
	username = new QLineEdit(this);
	email = new QLineEdit(this);
	password = new QLineEdit(this);
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	SetSize();
	StyleElements();
	PlaceElements();
	connect(loginButton, &QPushButton::clicked, controller, [controller]() {
		controller->showPage("Login");
		});
	connect(registerButton, &QPushButton::clicked, this, &RegisterPage::RegisterButtonClicked);
}

void RegisterPage::PlaceElements()
{
	setLayout(layout);

	QHBoxLayout* innerLayout = new QHBoxLayout;
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	innerLayout->addWidget(imageLabel);
	innerLayout->setContentsMargins(55, 0, 0, 70);

	layout->setContentsMargins(400, 100, 400, 100);
	layout->addLayout(innerLayout);
	layout->addWidget(username);
	layout->addWidget(email);
	layout->addWidget(password);
	layout->addWidget(registerButton);
	layout->addWidget(loginButton);
	layout->setAlignment(Qt::AlignCenter);
}

void RegisterPage::StyleElements()
{
	password->setEchoMode(QLineEdit::Password);
	username->setPlaceholderText("Username");
	email->setPlaceholderText("Email");
	password->setPlaceholderText("Password");
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void RegisterPage::SetSize()
{
	username->setFixedSize(400, 50);
	email->setFixedSize(400, 50);
	password->setFixedSize(400, 50);
	loginButton->setFixedSize(400, 50);
	registerButton->setFixedSize(400, 50);
	username->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	email->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	password->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	loginButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	registerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void RegisterPage::RegisterButtonClicked()
{
}
