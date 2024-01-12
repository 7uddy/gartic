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
	innerLayout = new QHBoxLayout;
	SetSize();
	StyleElements();
	PlaceElements();
	connect(loginButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("Login");
		});
	connect(registerButton, &QPushButton::clicked, controller, [=]() {
		if (controller->VerifyRegister(username->text(),email->text(), password->text()))
		{
			QMessageBox::information(controller, "Registration Success", "User registered successfully. You can now log in.");
			controller->ShowPage("Login");
		}
		else 
		{
			QMessageBox::warning(controller, "Register Error", "Invalid username or password or email.");
		}
		});
}

void RegisterPage::PlaceElements()
{
	setLayout(layout);
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	innerLayout->addWidget(imageLabel);
	innerLayout->setAlignment(Qt::AlignCenter);

	layout->addSpacing(50);
	layout->addLayout(innerLayout);
	layout->addWidget(username);
	layout->addSpacing(5);
	layout->addWidget(email);
	layout->addSpacing(5);
	layout->addWidget(password);
	layout->addSpacing(20);
	layout->addWidget(registerButton);
	layout->addSpacing(5);
	layout->addWidget(loginButton);
	layout->addSpacing(200);
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

RegisterPage::~RegisterPage()
{
	/*empty*/
}
