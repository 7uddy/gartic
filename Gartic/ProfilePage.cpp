#include "ProfilePage.h"

ProfilePage::ProfilePage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	username = new QTextEdit("Username", this);
	averageScore = new QTextEdit("Average Score", this);
	matchHistory = new QTextEdit("Match History", this);
	topLayout = new QHBoxLayout(this);
	infoLayout = new QVBoxLayout(this);
	buttonLayout = new QHBoxLayout(this);
	returnButton = new QPushButton(this);
	SetSize();
	StyleElements();
	PlaceElements();
	connect(returnButton, &QPushButton::clicked, controller, [controller]() {
		controller->showPage("MainMenu");
		});
}

void ProfilePage::PlaceElements()
{
	setLayout(layout);
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	imageLabel->setFixedSize(image.width(), image.height());
	topLayout->addWidget(imageLabel);
	topLayout->setAlignment(imageLabel, Qt::AlignLeft);

	infoLayout->addWidget(username);
	infoLayout->addSpacing(5);
	infoLayout->addWidget(averageScore);
	infoLayout->addSpacing(5);
	infoLayout->addWidget(matchHistory);
	infoLayout->setAlignment(Qt::AlignCenter);

	buttonLayout->addWidget(returnButton);

	layout->addLayout(topLayout);
	layout->addLayout(infoLayout);
	layout->addSpacing(100);
	layout->addLayout(buttonLayout);
	layout->setAlignment(topLayout, Qt::AlignTop);
	layout->setAlignment(infoLayout, Qt::AlignCenter);
	layout->setAlignment(buttonLayout, Qt::AlignLeft);
}

void ProfilePage::StyleElements()
{
	username->setReadOnly(true);
	averageScore->setReadOnly(true);
	matchHistory->setReadOnly(true);
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	returnButton->setAccessibleName("returnButton");
	setStyleSheet(styleSheet);
}

void ProfilePage::SetSize()
{
	username->setFixedSize(200, 50);
	averageScore->setFixedSize(200, 50);
	matchHistory->setFixedSize(200, 350);
	username->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	averageScore->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	matchHistory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

ProfilePage::~ProfilePage()
{
	delete  layout, infoLayout, topLayout, buttonLayout, imageLabel, username, 
		averageScore, matchHistory, returnButton;
}
