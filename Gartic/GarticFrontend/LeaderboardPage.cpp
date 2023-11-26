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

	middleLayout->addWidget(boardPadding);
	middleLayout->setAlignment(Qt::AlignCenter);

	layout->addLayout(middleLayout);
	layout->addLayout(topLeftLayout);
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

LeaderboardPage::~LeaderboardPage()
{
	delete imageLabel, returnButton, layout;
}
