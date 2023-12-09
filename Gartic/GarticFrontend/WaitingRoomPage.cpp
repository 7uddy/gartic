#include "WaitingRoomPage.h"

WaitingRoomPage::WaitingRoomPage(PageController* controller, QWidget* parent)
{
	startButton = new QPushButton("Start", this);
	easyButton = new QPushButton("Easy", this);
	mediumButton = new QPushButton("Medium", this);
	hardButton = new QPushButton("Hard", this);
	imageLabel = new QLabel(this);
	topLayout = new QHBoxLayout();
	layout = new QVBoxLayout(this);
	listPlayers = new QTextEdit("Players list", this);
	status = new QTextEdit("Waiting...", this); //will be modify
	infoGame = new QHBoxLayout();
	infoPlayers = new QVBoxLayout();
	playersNumber = new QTextEdit("Players: ?/4", this);
	roomCode = new QTextEdit("Room code: ???", this); //will be modify
	difficulty = new QTextEdit("Difficulty:", this);
	roomInfo = new QVBoxLayout();
	buttonsLayout = new QHBoxLayout();
	SetSize();
	StyleElements();
	PlaceElements();
	connect(startButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("Game"); // just testing
		});
}

void WaitingRoomPage::PlaceElements()
{
	setLayout(layout);
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	imageLabel->setFixedSize(image.width(), image.height());
	topLayout->addWidget(imageLabel);
	topLayout->setAlignment(imageLabel, Qt::AlignLeft);

	infoPlayers->addWidget(playersNumber);
	infoPlayers->addWidget(listPlayers);

	roomInfo->addWidget(status);
	roomInfo->setAlignment(status, Qt::AlignTop);
	roomInfo->addWidget(roomCode);
	roomInfo->setAlignment(roomCode, Qt::AlignTop);
	roomInfo->addWidget(difficulty);
	roomInfo->setAlignment(difficulty, Qt::AlignCenter);
	buttonsLayout->addWidget(easyButton);
	buttonsLayout->addWidget(mediumButton);
	buttonsLayout->addWidget(hardButton);
	roomInfo->addLayout(buttonsLayout);
	roomInfo->addWidget(startButton);
	roomInfo->setAlignment(startButton, Qt::AlignCenter);

	infoGame->addLayout(infoPlayers);
	infoGame->addLayout(roomInfo);

	layout->addLayout(topLayout);
	layout->addLayout(infoGame);
	layout->addSpacing(200);
	layout->setAlignment(topLayout, Qt::AlignTop);
	layout->setAlignment(infoGame, Qt::AlignCenter);
}

void WaitingRoomPage::StyleElements()
{
	listPlayers->setReadOnly(true);
	status->setReadOnly(true);
	playersNumber->setReadOnly(true);
	roomCode->setReadOnly(true);
	difficulty->setReadOnly(true);
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void WaitingRoomPage::SetSize()
{
	startButton->setFixedSize(200, 50);
	easyButton->setFixedSize(200, 50);
	mediumButton->setFixedSize(200, 50);
	hardButton->setFixedSize(200, 50);
	listPlayers->setFixedSize(200, 350);
	status->setFixedSize(200, 50);
	playersNumber->setFixedSize(200, 50);
	roomCode->setFixedSize(200, 50);
	difficulty->setFixedSize(200, 50);
	startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	easyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	mediumButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	hardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	listPlayers->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	status->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	playersNumber->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	roomCode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	difficulty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

WaitingRoomPage::~WaitingRoomPage()
{
	delete startButton, easyButton, mediumButton, hardButton, imageLabel, topLayout, infoGame,
		buttonsLayout, layout, infoPlayers, roomInfo, listPlayers, status, playersNumber,
		roomCode, difficulty;
}

