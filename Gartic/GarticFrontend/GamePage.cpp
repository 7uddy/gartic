#include "GamePage.h"

GamePage::GamePage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	topLayout = new QHBoxLayout();
	listPlayers = new QTextEdit("Players:", this);
	round = new QTextEdit("Round: ?/4", this);
	time = new QTextEdit("Time: ???", this);
	word = new QTextEdit("????", this);
	chatLayout = new QVBoxLayout();
	messageInput = new QLineEdit(this);
	sendButton = new QPushButton("Send", this);
	chatHistory = new QTextEdit(this);
	connect(sendButton, &QPushButton::clicked, this, &GamePage::SendMessage);
}

void GamePage::PlaceElements()
{
	setLayout(layout);
	QPixmap image("Images/Title.png");
	imageLabel->setPixmap(image);
	imageLabel->setFixedSize(image.width(), image.height());
	topLayout->addWidget(imageLabel);

	topLayout->setAlignment(imageLabel, Qt::AlignLeft);
	topLayout->addWidget(round);
	topLayout->setAlignment(round, Qt::AlignRight);
	topLayout->addWidget(time);
	topLayout->setAlignment(time, Qt::AlignRight);
	topLayout->addWidget(word);
	topLayout->setAlignment(word, Qt::AlignRight);

	chatLayout->addWidget(chatHistory);
	chatLayout->addWidget(messageInput);
	chatLayout->addWidget(sendButton);

	layout->addLayout(topLayout);
	layout->addLayout(chatLayout);
	layout->setAlignment(topLayout, Qt::AlignTop);
	layout->setAlignment(chatLayout, Qt::AlignBottom | Qt::AlignRight);
}

void GamePage::StyleElements()
{
	/*empty*/
}

void GamePage::SetSize()
{
	/*empty*/
}

void GamePage::SendMessage()
{
	QString message = messageInput->text();
	if (!message.isEmpty()) 
	{
		chatHistory->append("Name: " + message);
		messageInput->clear();
	}
}

GamePage::~GamePage()
{
	delete imageLabel, listPlayers, round, time, word, topLayout, layout, chatLayout, messageInput,
		sendButton, chatHistory;
}
