#include "LeaderboardPage.h"

LeaderboardPage::LeaderboardPage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	returnButton = new QPushButton(this);

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

	QWidget* boardPadding = new QWidget;
	boardPadding->setAccessibleName("leaderboardPadding");
	boardPadding->setFixedSize(500, 300);


	QWidget* profilePadding = new QWidget(boardPadding);
	profilePadding->setAccessibleName("profilePadding");
	profilePadding->setFixedSize(300, 100);


	QHBoxLayout* profileLayout = new QHBoxLayout(profilePadding);

	QLabel* profileImage = new QLabel;
	profileImage->setPixmap(QPixmap("Images/arrow_pressed.png"));
	profileImage->setFixedSize(50, 50);
	profileImage->setScaledContents(true);

	QLabel* profileName = new QLabel;
	profileName->setText("Player1");

	QLabel* profileScore = new QLabel;
	profileScore->setText("110");

	profileLayout->addWidget(profileImage);
	profileLayout->addWidget(profileName);
	profileLayout->addWidget(profileScore);


	middleLayout->addWidget(boardPadding);
	middleLayout->setAlignment(Qt::AlignCenter);


	
	layout->addLayout(topLeftLayout);
	layout->addLayout(middleLayout);
	layout->addLayout(bottomLeftLayout);
}

void LeaderboardPage::StyleElements()
{
	returnButton->setAccessibleName("returnButton");
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

}

LeaderboardPage::~LeaderboardPage()
{
	delete imageLabel, returnButton, layout;
}
