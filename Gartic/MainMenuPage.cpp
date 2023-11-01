#include "MainMenuPage.h"

MainMenuPage::MainMenuPage(PageController* controller, QWidget* parent)
{
	//myProfile = new QPushButton("My profile", this); // will be modified
	createButton = new QPushButton("Create room", this);
	joinButton = new QPushButton("Join room", this);
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	SetSize();
	StyleElements();
	PlaceElements();
	connect(createButton, &QPushButton::clicked, this, &MainMenuPage::CreateButtonClicked);
	connect(joinButton, &QPushButton::clicked, this, &MainMenuPage::JoinButtonClicked);
}

void MainMenuPage::PlaceElements()
{
	setLayout(layout);
	layout->setContentsMargins(400, 100, 400, 100);
	layout->addWidget(createButton);
	layout->addWidget(joinButton);
	layout->setAlignment(Qt::AlignCenter);

	QHBoxLayout* layout2 = new QHBoxLayout;
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	imageLabel->setFixedSize(image.width(), image.height());
	layout2->addWidget(imageLabel);
	layout2->setAlignment(Qt::AlignTop | Qt::AlignLeft);

}

void MainMenuPage::StyleElements()
{
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void MainMenuPage::SetSize()
{
	createButton->setFixedSize(400, 100);
	joinButton->setFixedSize(400, 100);
	createButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	joinButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void MainMenuPage::CreateButtonClicked()
{
}

void MainMenuPage::JoinButtonClicked()
{
}
