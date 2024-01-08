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
	code = new QPushButton("Press here");
	currentDifficulty = Difficulty::Easy;

	connect(difficultyButton, &QPushButton::clicked, this, [=]() {
		currentDifficulty = static_cast<Difficulty>((difficultyToInt(currentDifficulty) + 1) % 4);
		difficultyButton->setText(difficultyToQString(currentDifficulty));
		});

	connect(startButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("Game");
		});

	connect(returnButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("MainMenu");
		});
	connect(code, &QPushButton::clicked, this, [=]()
	    {
			UpdateLobbyCode(controller->GetLobbyCode());
	    });
	SetSize();
	StyleElements();
	PlaceElements();
}

void WaitingRoomPage::PlaceElements()
{
	setLayout(layout);
	QHBoxLayout* topLeftLayout = new QHBoxLayout;
	QPixmap image("Images/Game_Name.png");
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
	statusText->setAccessibleName("statusLabel");
	statusLayout->addWidget(statusText);
	statusLayout->addWidget(playersNumber, 0, Qt::AlignRight);


	QGridLayout* mainPaddingLayout = new QGridLayout;
	QLabel* roomCode = new QLabel("Room Code");
	QLabel* difficulty = new QLabel("Difficulty");

	mainPaddingLayout->addWidget(roomCode, 0, 0, Qt::AlignCenter);
	mainPaddingLayout->addWidget(code, 0, 1, Qt::AlignCenter);

	roomCode->setAlignment(Qt::AlignLeft);

	mainPaddingLayout->addWidget(difficulty, 1, 0, Qt::AlignCenter);
	mainPaddingLayout->addWidget(difficultyButton, 1, 1, Qt::AlignCenter);
	mainPaddingLayout->setRowStretch(1, 0);


	QVBoxLayout* roomSettingLayout = new QVBoxLayout(mainPadding);
	roomSettingLayout->addLayout(mainPaddingLayout);
	roomSettingLayout->addWidget(startButton, 0, Qt::AlignCenter | Qt::AlignBottom);

	QPushButton* testButton = new QPushButton("Test me");
	middleLayout->addWidget(testButton, 0, 0);

	connect(testButton, &QPushButton::clicked, this, [=]() {
		OnPlayerJoin("Caramel"); //for testing
		});

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
	returnButton->setAccessibleName("returnButton");
	difficultyButton->setAccessibleName("difficultyButton");
	startButton->setAccessibleName("startButton");
	mainPadding->setAccessibleName("mainPadding");
	playersNumber->setAccessibleName("statusLabel");
	code->setAccessibleName("codeButton");

	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void WaitingRoomPage::SetSize()
{
	mainPadding->setFixedSize(600, 300);
	difficultyButton->setFixedSize(90, 30);
	profilesLayout->setSpacing(2);
	code->setFixedSize(110, 30);

	returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void WaitingRoomPage::OnPlayerJoin(const QString& playerName)
{
	QWidget* newProfilePadding = new QWidget;
	newProfilePadding->setAccessibleName("profilePadding");
	newProfilePadding->setFixedSize(300, 60);

	profilesLayout->addWidget(newProfilePadding);

	QHBoxLayout* newProfileLayout = new QHBoxLayout(newProfilePadding);

	QLabel* newProfileImage = new QLabel;
	newProfileImage->setPixmap(QPixmap("Images/[PNG] App_icon.png"));
	newProfileImage->setFixedSize(40, 40);
	newProfileImage->setScaledContents(true);

	QLabel* newProfileName = new QLabel;
	newProfileName->setText(playerName);

	newProfileLayout->addWidget(newProfileImage, Qt::AlignLeft);
	newProfileLayout->addWidget(newProfileName);
	newProfileLayout->setAlignment(Qt::AlignCenter);

	newProfilePadding->setVisible(true);
	newProfileImage->setVisible(true);
	newProfileName->setVisible(true);

	profilePaddings.append(newProfilePadding);
	profileLayouts.append(newProfileLayout);
	// profileNames.append(newProfileName);

	 UpdateMainPaddingSize();

	playersNumber->setText(QString::number(profilePaddings.size()) + "/4");
}

void WaitingRoomPage::UpdateMainPaddingSize()
{
	int totalProfilesHeight = 0;
	for (int index = 0; index < profilePaddings.size(); ++index)
	{
		totalProfilesHeight += profilePaddings[index]->height();
	}

	if (totalProfilesHeight > mainPadding->height())
	{
		mainPadding->setFixedHeight(totalProfilesHeight);
		mainPadding->setFixedWidth(mainPadding->width() + 10);
	}
}

void WaitingRoomPage::UpdateLobbyCode(const std::string& codeLobby)
{
	lobbyCode = codeLobby;
	code->setText(QString::fromUtf8(codeLobby.c_str()));
	code->setEnabled(false);
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
	delete layout, profilesLayout, imageLabel, returnButton, startButton,
		mainPadding, difficultyButton, playersNumber,
		profilePaddings, profileLayouts;
}

