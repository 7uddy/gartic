#include "WaitingRoomPage.h"

WaitingRoomPage::WaitingRoomPage(PageController* controller, QWidget* parent)
{
	startButton = new QPushButton("Start",this);
	easyButton = new QPushButton("Easy",this);
	mediumButton = new QPushButton("Medium",this);
	hardButton = new QPushButton("Hard",this);
	imageLabel = new QLabel(this);
	topLayout = new QHBoxLayout(this);
	layout = new QVBoxLayout(this);
	listPlayers = new QTextEdit("Players list", this);
	status = new QTextEdit("Waiting..", this); //will be modify
	playersInfo = new QVBoxLayout(this);
    infoGame= new QVBoxLayout(this);
	playersNumber = new QTextEdit("Players: ?/4", this);
	roomCode = new QTextEdit("Room code: ???", this); //will be modify
	difficulty = new QTextEdit("Difficulty:", this);
	roomInfo = new QHBoxLayout(this);
	SetSize();
	StyleElements();
	PlaceElements();
}

void WaitingRoomPage::PlaceElements()
{
    setLayout(layout);
    QPixmap image("Images/Title.png");
    imageLabel->setPixmap(image);
    imageLabel->setFixedSize(image.width(), image.height());
    topLayout->addWidget(imageLabel);
    topLayout->setAlignment(imageLabel,Qt::AlignLeft|Qt::AlignTop);

	playersInfo->addWidget(listPlayers);
	playersInfo->addWidget(roomCode);
	playersInfo->setAlignment(Qt::AlignLeft);

	infoGame->addWidget(status);
	infoGame->addWidget(playersNumber);
	infoGame->addWidget(roomCode);
	infoGame->addWidget(difficulty);

	roomInfo->addLayout(playersInfo);
	roomInfo->addLayout(infoGame);
	roomInfo->setAlignment(playersInfo, Qt::AlignLeft);
	roomInfo->setAlignment(infoGame, Qt::AlignRight);

    layout->addLayout(topLayout);
	layout->addLayout(roomInfo);
    layout->setAlignment(topLayout, Qt::AlignTop);
	layout->setAlignment(roomInfo, Qt::AlignCenter);
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
	listPlayers->setFixedSize(200, 350);
	status->setFixedSize(200, 50);
	playersNumber->setFixedSize(200, 50);
	roomCode->setFixedSize(200, 50);
	difficulty->setFixedSize(200, 50);
	listPlayers->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	status->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	playersNumber->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	roomCode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	difficulty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	easyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	mediumButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	hardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

WaitingRoomPage::~WaitingRoomPage()
{
	delete startButton, easyButton, mediumButton, hardButton, imageLabel, topLayout,listPlayers, 
        status,playersInfo,infoGame,playersNumber,roomCode,difficulty;
}

