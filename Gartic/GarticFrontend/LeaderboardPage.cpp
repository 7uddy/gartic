#include "LeaderboardPage.h"

LeaderboardPage::LeaderboardPage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	returnButton = new QPushButton(this);
	boardPadding = new QWidget;
	topLeftLayout = new QHBoxLayout;
	bottomLeftLayout = new QVBoxLayout;
	middleLayout = new QVBoxLayout;
	isGameFinished = false;
	title = new QLabel("Leaderboard",this);
	index = 0;
	SetSize();
	StyleElements();
	PlaceElements();
	connect(returnButton, &QPushButton::clicked, controller, [=]() {
		ClearPlayerProfiles();
		controller->ShowPage("MainMenu");
		});
}

void LeaderboardPage::PlaceElements()
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

	boardPadding->setFixedSize(400, 350);
	middleLayout->addWidget(title);
	middleLayout->addWidget(boardPadding);
	middleLayout->setAlignment(Qt::AlignCenter);

	layout->addLayout(topLeftLayout);
	layout->addLayout(middleLayout);
	layout->addLayout(bottomLeftLayout);
}

void LeaderboardPage::StyleElements()
{
	returnButton->setAccessibleName("returnButton");
	boardPadding->setAccessibleName("mainPadding");
	title->setAccessibleName("title");
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void LeaderboardPage::SetSize()
{
	returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void LeaderboardPage::UpdateData()
{
	auto responsePlayers = cpr::Get(
		cpr::Url{ "http://localhost:18080/getplayersandrequestend" }
	);
	auto players = nlohmann::json::parse(responsePlayers.text);
	for (const auto& player : players)
	{
		AddPlayer(QString::fromUtf8(player["username"].get<std::string>()), QString::fromUtf8(player["score"].get<std::string>()));
	}
}

void LeaderboardPage::showEvent(QShowEvent* event)
{
	if (!isGameFinished)
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, "Game", "The game has ended.", QMessageBox::Ok);
		if (reply == QMessageBox::Ok)
		{
			UpdateData();
		}
		isGameFinished = true;
	}
	QWidget::showEvent(event);
}

void LeaderboardPage::AddPlayer(const QString& playerName, const QString& playerScore)
{
	QWidget* newProfilePadding = new QWidget(boardPadding);
	newProfilePadding->setAccessibleName("profilePadding");
	newProfilePadding->setFixedSize(380, 70);
	newProfilePadding->setGeometry(10, 20 + 80 * index, 0, 0);

	QHBoxLayout* newProfileLayout = new QHBoxLayout(newProfilePadding);

	QLabel* newProfileImage = new QLabel;
	newProfileImage->setPixmap(QPixmap("Images/[PNG] App_icon.png"));
	newProfileImage->setFixedSize(40, 40);
	newProfileImage->setScaledContents(true);

	QLabel* newProfileName = new QLabel;
	newProfileName->setText(playerName);

	QLabel* newProfileScore = new QLabel;
	newProfileScore->setText(playerScore);

	newProfileLayout->addWidget(newProfileImage, Qt::AlignLeft);
	newProfileLayout->addWidget(newProfileName);
	newProfileLayout->addWidget(newProfileScore, 0, Qt::AlignRight);
	newProfileLayout->setAlignment(Qt::AlignCenter);

	newProfilePadding->setVisible(true);
	newProfileImage->setVisible(true);
	newProfileName->setVisible(true);
	newProfileScore->setVisible(true);

	profilePaddings.append(newProfilePadding);
	profileLayouts.append(newProfileLayout);
	profileImages.append(newProfileImage);
	profileNames.append(newProfileName);
	profileScores.append(newProfileScore);

	index++;
}

void LeaderboardPage::ClearPlayerProfiles()
{
	for (int index = 0; index < profilePaddings.size(); index++)
	{
		delete profilePaddings[index];
	}
	profilePaddings.clear();
	profileLayouts.clear();
	profileNames.clear();
}

LeaderboardPage::~LeaderboardPage()
{
	/*empty*/
}
