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

	
	SetSize();
	StyleElements();
	PlaceElements();

	connect(startButton, &QPushButton::clicked, controller, [controller]() {
		controller->ShowPage("Game");
		});
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

WaitingRoomPage::~WaitingRoomPage()
{
	
}

