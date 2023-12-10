#include "WaitingRoomPage.h"

WaitingRoomPage::WaitingRoomPage(PageController* controller, QWidget* parent)
{
	layout = new QVBoxLayout(this);
	imageLabel = new QLabel(this);
	returnButton = new QPushButton(this);
	mainPadding = new QWidget;
	profilesLayout = new QVBoxLayout;
	difficultyButton = new QPushButton("Easy");
	startButton = new QPushButton("Start");
	playersNumber = new QLabel("0/4");

	currentDifficulty = Difficulty::Easy;

	connect(difficultyButton, &QPushButton::clicked, this, [=]() {
		currentDifficulty = static_cast<Difficulty>((difficultyToInt(currentDifficulty) + 1) % 4);
		difficultyButton->setText(difficultyToQString(currentDifficulty));
		});

	connect(startButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("Game");
		});


	SetSize();
	StyleElements();
	PlaceElements();
}

void WaitingRoomPage::PlaceElements()
{
	setLayout(layout);
	QHBoxLayout* topLeftLayout = new QHBoxLayout;
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	topLeftLayout->addWidget(imageLabel);
	topLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	QVBoxLayout* bottomLeftLayout = new QVBoxLayout;
	returnButton->setIconSize(QSize(50, 50));
	returnButton->setFixedSize(40, 40);
	bottomLeftLayout->addWidget(returnButton);
	bottomLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	QGridLayout* middleLayout = new QGridLayout;

	QHBoxLayout* statusLayout = new QHBoxLayout;
	QLabel* statusText = new QLabel("Waiting..");
	statusLayout->addWidget(statusText);
	statusLayout->addWidget(playersNumber, 0, Qt::AlignRight);


	QGridLayout* mainPaddingLayout = new QGridLayout;
	QLabel* roomCode = new QLabel("Room Code");
	QLabel* code = new QLabel("AB345");
	QLabel* difficulty = new QLabel("Difficulty");

	mainPaddingLayout->addWidget(roomCode, 0, 0, Qt::AlignCenter);
	mainPaddingLayout->addWidget(code, 0, 1, Qt::AlignCenter);

	roomCode->setAlignment(Qt::AlignLeft);
	code->setAlignment(Qt::AlignCenter | Qt::AlignRight);

	mainPaddingLayout->addWidget(difficulty, 1, 0, Qt::AlignCenter);
	mainPaddingLayout->addWidget(difficultyButton, 1, 1, Qt::AlignCenter);
	mainPaddingLayout->setRowStretch(1, 0);


	QVBoxLayout* roomSettingLayout = new QVBoxLayout(mainPadding);
	roomSettingLayout->addLayout(mainPaddingLayout);
	roomSettingLayout->addWidget(startButton, 0, Qt::AlignCenter | Qt::AlignBottom);



	middleLayout->addLayout(statusLayout, 0, 1);
	middleLayout->addLayout(profilesLayout, 1, 0);
	middleLayout->addWidget(mainPadding, 1, 1, Qt::AlignTop);
	middleLayout->setAlignment(Qt::AlignCenter);

	layout->addLayout(topLeftLayout);
	layout->addLayout(middleLayout);
	layout->addLayout(bottomLeftLayout);

}

void WaitingRoomPage::StyleElements()
{
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void WaitingRoomPage::SetSize()
{
	returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QString WaitingRoomPage::difficultyToQString(Difficulty difficulty) {
	if (difficulty == Difficulty::Easy)
		return "Easy";
	if (difficulty == Difficulty::Medium)
		return "Medium";
	if (difficulty == Difficulty::Hard)
		return "Hard";
	if (difficulty == Difficulty::Ascending)
		return "Ascending";

	throw std::exception("Unable to convert difficulty to QString");
}

int WaitingRoomPage::difficultyToInt(Difficulty difficulty) {
	if (difficulty == Difficulty::Easy)
		return 0;
	if (difficulty == Difficulty::Medium)
		return 1;
	if (difficulty == Difficulty::Hard)
		return 2;
	if (difficulty == Difficulty::Ascending)
		return 3;

	throw std::exception("Unable to convert difficulty to int");
}

WaitingRoomPage::~WaitingRoomPage()
{
	
}

