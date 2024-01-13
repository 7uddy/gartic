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
	playersNumber = new QLabel("0/6");
	code = new QPushButton("Press here");
	currentDifficulty = Difficulty::Easy;
	statusText = new QLabel();
	timer = new QTimer(this);
	topLeftLayout = new QHBoxLayout;
	bottomLeftLayout = new QVBoxLayout;
	middleLayout = new QGridLayout;
	statusLayout = new QHBoxLayout;
	mainPaddingLayout = new QGridLayout;
	roomCode = new QLabel("Room Code");
    difficulty = new QLabel("Difficulty");
	roomSettingLayout = new QVBoxLayout(mainPadding);
	m_controller = controller;
	SetSize();
	StyleElements();
	PlaceElements();
	SetConnections();
}

void WaitingRoomPage::PlaceElements()
{
	setLayout(layout);
	QPixmap image("Images/Game_Name.png");
	imageLabel->setPixmap(image);
	topLeftLayout->addWidget(imageLabel);
	topLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	returnButton->setIconSize(QSize(50, 50));
	returnButton->setFixedSize(40, 40);
	bottomLeftLayout->addWidget(returnButton);
	bottomLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	statusText->setAccessibleName("statusLabel");
	statusLayout->addWidget(statusText);
	statusLayout->addWidget(playersNumber, 0, Qt::AlignRight);

	mainPaddingLayout->addWidget(roomCode, 0, 0, Qt::AlignCenter);
	mainPaddingLayout->addWidget(code, 0, 1, Qt::AlignCenter);

	roomCode->setAlignment(Qt::AlignLeft);

	mainPaddingLayout->addWidget(difficulty, 1, 0, Qt::AlignCenter);
	mainPaddingLayout->addWidget(difficultyButton, 1, 1, Qt::AlignCenter);
	mainPaddingLayout->setRowStretch(1, 0);

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

void WaitingRoomPage::SetConnections()
{
	connect(difficultyButton, &QPushButton::clicked, this, [=]() {
		if (ownerRoom)
		{
			currentDifficulty = static_cast<Difficulty>((DifficultyToInt(currentDifficulty) + 1) % 4);
			difficultyButton->setText(DifficultyToQString(currentDifficulty));
		}
		});
	connect(startButton, &QPushButton::clicked, m_controller, [=]() {
		if (ownerRoom)
		{
			timer->stop();
			if (m_controller->StartGame(DifficultyToInt(currentDifficulty)))
				m_controller->ShowPage("Game");
		}
		});
	connect(returnButton, &QPushButton::clicked, m_controller, [=]() {
		if (m_controller->LeaveRoom())
		{
			timer->stop();
			code->setEnabled(true);
			code->setText("Press here");
			m_controller->ShowPage("MainMenu");
		}
		else
			QMessageBox::warning(m_controller, "Exit Room Error", "Something went wrong.");
		});
	connect(code, &QPushButton::clicked, this, [=]()
		{
			UpdateRoomCode(m_controller->GetLobbyCode(), m_controller->GetOwner());
		});
	connect(timer, &QTimer::timeout, this, &WaitingRoomPage::UpdateDataFromRoom);
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
	profileNames.append(newProfileName);

	UpdateMainPaddingSize();

	playersNumber->setText(QString::number(profilePaddings.size()) + "/6");
}

//void WaitingRoomPage::OnPlayerLeave(const int& index)
//{
//	profileNames.erase(profileNames.begin() + index);
//	profilePaddings.erase(profilePaddings.begin() + index);
//	profileLayouts.erase(profileLayouts.begin() + index);
//	UpdateMainPaddingSize();
//	playersNumber->setText(QString::number(profilePaddings.size()) + "/6");
//}

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

void WaitingRoomPage::UpdateDataFromRoom()
{
	auto responseStatus = cpr::Get(
		cpr::Url{ "http://localhost:18080/getlobbystatus" },
		cpr::Parameters{
				{ "lobbycode", codeRoom},
		}
	);
	if (responseStatus.status_code != 200)
		return;
	if (responseStatus.text == "0")
		statusText->setText("WaitingForPlayers");
	else
	{
		timer->stop();
		statusText->setText("Launched");
		m_controller->ShowPage("Game");
		return;
	}

	auto responsePlayers = cpr::Get(
		cpr::Url{ "http://localhost:18080/getusernamesfromlobby" },
		cpr::Parameters{
				{ "lobbycode", codeRoom},
		}
	);
	if (responseStatus.status_code != 200)
		return;
	auto players = nlohmann::json::parse(responsePlayers.text);
	for (const auto& player : players)
	{
		if((oldPlayers.empty())|| (std::find(oldPlayers.begin(),oldPlayers.end(), player["username"].get<std::string>())==oldPlayers.end()))
		{
			OnPlayerJoin(QString::fromUtf8(player["username"].get<std::string>()));
			oldPlayers.push_back(player["username"].get<std::string>());
		}
	}
	/*for (int index = 0; index < profileNames.size(); index++)
	{
		const QString playerName = profileNames[index]->text(); 
		auto it = std::find_if(players.begin(), players.end(), [&](const auto& player) {
			return player["username"].get<std::string>() == playerName.toStdString();
			});

		if (it == players.end())
		{
			OnPlayerLeave(index);
		}
	}*/
	timer->start(2000);
}

void WaitingRoomPage::UpdateRoomCode(const std::string& codeLobby, const bool& owner)
{
	player = m_controller->GetPlayer();
	ownerRoom = owner;
	codeRoom = codeLobby;
	code->setText(QString::fromUtf8(codeLobby.c_str()));
	code->setEnabled(false);
	UpdateDataFromRoom();
}

QString WaitingRoomPage::DifficultyToQString(Difficulty difficulty) {
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

int WaitingRoomPage::DifficultyToInt(Difficulty difficulty) {
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
	/*empty*/
}

