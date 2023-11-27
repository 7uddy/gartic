#include "LeaderboardPage.h"

LeaderboardPage::LeaderboardPage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	returnButton = new QPushButton(this);
	boardPadding = new QWidget;

	SetSize();
	StyleElements();
	PlaceElements();
}

void LeaderboardPage::PlaceElements()
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

	QVBoxLayout* middleLayout = new QVBoxLayout;
	boardPadding->setFixedSize(400, 350);

	middleLayout->addWidget(boardPadding);
	middleLayout->setAlignment(Qt::AlignCenter);

	layout->addLayout(topLeftLayout);
	layout->addLayout(middleLayout);
	layout->addLayout(bottomLeftLayout);
}

void LeaderboardPage::StyleElements()
{
	returnButton->setAccessibleName("returnButton");
	boardPadding->setAccessibleName("leaderboardPadding");

	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void LeaderboardPage::SetSize()
{
	returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void LeaderboardPage::OnPlayerJoin(const QString& playerName, const QString& playerScore)
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

	profilePaddings.append(newProfilePadding);
	profileLayouts.append(newProfileLayout);
	profileImages.append(newProfileImage);
	profileNames.append(newProfileName);
	profileScores.append(newProfileScore);

	index++;
}

LeaderboardPage::~LeaderboardPage()
{
	delete imageLabel, returnButton, layout;
}
