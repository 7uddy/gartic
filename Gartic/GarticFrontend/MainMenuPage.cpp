#include "MainMenuPage.h"

MainMenuPage::MainMenuPage(PageController* controller, QWidget* parent)
{
	myProfile = new QPushButton("My profile", this);
	createButton = new QPushButton("Create room", this);
	joinButton = new QPushButton("Join room", this);
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	buttonsLayout = new QVBoxLayout(this);
	topLayout = new QHBoxLayout(this);
	SetSize();
	StyleElements();
	PlaceElements();
	connect(createButton, &QPushButton::clicked, controller, [controller]() {
		if (controller->CreateRoom())
			controller->ShowPage("WaitingRoom");
		else 
			QMessageBox::warning(controller, "Create Room Error", "A room is already created or something went wrong.");
		});
	connect(joinButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("SelectRoom");
		});
	connect(myProfile, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("Profile");
		});
}

void MainMenuPage::PlaceElements()
{
	setLayout(layout);
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	imageLabel->setFixedSize(image.width(), image.height());

	topLayout->addWidget(imageLabel);
	topLayout->addWidget(myProfile);
	topLayout->setAlignment(imageLabel, Qt::AlignLeft);
	topLayout->setAlignment(myProfile, Qt::AlignRight);
	
	buttonsLayout->addWidget(createButton);
	buttonsLayout->addSpacing(20);
	buttonsLayout->addWidget(joinButton);

	layout->addLayout(topLayout);
	layout->addLayout(buttonsLayout);
	layout->addSpacing(200);
	layout->setAlignment(topLayout, Qt::AlignTop);
	layout->setAlignment(buttonsLayout, Qt::AlignCenter);
}

void MainMenuPage::StyleElements()
{
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	myProfile->setAccessibleName("myProfile");
	setStyleSheet(styleSheet);
}

void MainMenuPage::SetSize()
{
	createButton->setFixedSize(400, 100);
	joinButton->setFixedSize(400, 100);
	createButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	joinButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

MainMenuPage::~MainMenuPage()
{
	/*empty*/
}

