#include "../includes/ProfilePage.h"

ProfilePage::ProfilePage(PageController* controller, QWidget* parent)
{
	layout = new QVBoxLayout(this);
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
	connect(sharedElements.GetReturnButton(), &QPushButton::clicked, controller, [=]() {
		matchHistory->setText("Match History: ");
		controller->ShowPage("MainMenu");
		});
}

void ProfilePage::PlaceElements()
{
	setLayout(layout);
	
	topLeftLayout->addWidget(sharedElements.GetImageLabel());
	topLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	bottomLeftLayout->addWidget(sharedElements.GetReturnButton());
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
	mainPadding->setAccessibleName("mainPadding");
	matchHistory->setAccessibleName("matchHistory");
	sharedElements.SetImagePhoto(QPixmap("resources//Title.png"));

	userImage->setPixmap(QPixmap("resources//[PNG] App_icon.png"));
	userImage->setFixedSize(150, 150);
	userImage->setScaledContents(true);
	QRegion* region = new QRegion(0, 0, userImage->width(), userImage->height(), QRegion::Ellipse);
	userImage->setMask(*region);

	QFile styleFile("resources//style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void ProfilePage::SetSize()
{
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
		std::string match,scoreText, matchText;
		float score;
		for (const auto& gameScore : gameScores)
		{
			
			if (gameScore.find("gameid") != gameScore.end())
			{
				matchText = gameScore["gameid"];
				match = "GameID: " + matchText;
			}
			if (gameScore.find("score") != gameScore.end())
			{
				scoreText = gameScore["score"];	
				score = std::stof(scoreText);
				match = match + "      " + "Score: " + std::to_string(score);
				matchHistory->append(QString::fromUtf8(match));
				scores.push_back(score);
			}
		}
	}
	if (!scores.empty())
		mediumScore = std::accumulate(scores.begin(), scores.end(), 0) / scores.size();
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
