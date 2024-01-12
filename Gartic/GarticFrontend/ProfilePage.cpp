#include "ProfilePage.h"

ProfilePage::ProfilePage(PageController* controller, QWidget* parent)
{
	layout = new QVBoxLayout(this);
	imageLabel = new QLabel(this);
	returnButton = new QPushButton(this);
	mainPadding = new QWidget;
	username = new QLabel;
	userImage = new QLabel;
	averageScore = new QLabel();
	matchHistory = new QTextEdit("Match History: ");
	m_controller = controller;
    topLeftLayout = new QHBoxLayout;
	bottomLeftLayout = new QVBoxLayout;
	middleLayout = new QVBoxLayout;
	mainPaddingLayout = new QHBoxLayout(mainPadding);
	leftSideLayout = new QVBoxLayout;
	SetSize();
	StyleElements();
	PlaceElements();
	connect(returnButton, &QPushButton::clicked, controller, [=]() {
		matchHistory->setText("Match History: ");
		controller->ShowPage("MainMenu");
		});
}

void ProfilePage::PlaceElements()
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

	middleLayout->addWidget(mainPadding);
	middleLayout->setAlignment(Qt::AlignCenter);

	leftSideLayout->addWidget(userImage);
	leftSideLayout->addWidget(username);
	leftSideLayout->addWidget(averageScore);

	mainPaddingLayout->addLayout(leftSideLayout);
	mainPaddingLayout->addWidget(matchHistory);

	layout->addLayout(topLeftLayout);
	layout->addLayout(middleLayout);
	layout->addLayout(bottomLeftLayout);
}

void ProfilePage::StyleElements()
{
	matchHistory->setEnabled(false);
	returnButton->setAccessibleName("returnButton");
	mainPadding->setAccessibleName("mainPadding");
	matchHistory->setAccessibleName("matchHistory");

	userImage->setPixmap(QPixmap("Images/[PNG] App_icon.png"));
	userImage->setFixedSize(150, 150);
	userImage->setScaledContents(true);
	QRegion* region = new QRegion(0, 0, userImage->width(), userImage->height(), QRegion::Ellipse);
	userImage->setMask(*region);

	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void ProfilePage::SetSize()
{
	returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mainPadding->setFixedSize(600, 500);
	matchHistory->setFixedSize(300, 400);
}

void ProfilePage::UpdateData()
{
	player = m_controller->GetPlayer();
	username->setText("Username:\n" + QString::fromUtf8(player.GetUsername().c_str()));
	auto responseProfileData = cpr::Get(
		cpr::Url{ "http://localhost:18080/getgamescores" },
		cpr::Parameters{
			{ "username", player.GetUsername()},
		}
	);
	if (responseProfileData.status_code != 200)
	{
		return;
	}
	auto gameScores = nlohmann::json::parse(responseProfileData.text);
	float mediumScore;
	std::vector<float> scores;
	if (gameScores.empty())
	{
		matchHistory->append("The player has not played any matches yet.");
	}
	else
	{
		matchHistory->clear();
		std::string match,score;
		for (const auto& gameScore : gameScores)
		{
			
			if (gameScore.find("gameid") != gameScore.end())
			{
				match = gameScore["gameid"];
			}
			if (gameScore.find("score") != gameScore.end())
			{
				score = gameScore["score"];
				match = match + "     " + score.substr(0, score.find('.') + 3);;
				matchHistory->append(QString::fromUtf8(match));
				scores.push_back(gameScore["score"].get<float>());
			}
		}
	}
	if (!scores.empty())
		mediumScore = static_cast<float>(std::accumulate(scores.begin(), scores.end(), 0)) / scores.size();
	else
		mediumScore = 0;
	QString score = QString::number(mediumScore, 'f', 2);
	averageScore->setText("Average score: " + score);
}

void ProfilePage::showEvent(QShowEvent* event)
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::information(this, "Profile", "You can access details about the matches played and the average score.", QMessageBox::Ok);
	if (reply == QMessageBox::Ok)
	{
		UpdateData();
	}
	QWidget::showEvent(event);
}

ProfilePage::~ProfilePage()
{
	/*empty*/
}
