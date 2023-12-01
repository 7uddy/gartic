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
	gameLayout = new QHBoxLayout();
	board = new BoardWidget();
	gameGridLayout = new QGridLayout();
	SetSize();
	StyleElements();
	PlaceElements();
	connect(sendButton, &QPushButton::clicked, this, &GamePage::SendMessage);
	connect(board, &BoardWidget::mouseDraw, this, &GamePage::updateBoard);
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
	topLayout->addSpacing(100);

	chatLayout->addWidget(chatHistory);
	chatLayout->addWidget(messageInput);
	chatLayout->addWidget(sendButton);

	gameGridLayout->setContentsMargins(20, 0, 20, 0);
	gameGridLayout->addWidget(listPlayers, 0, 0, 1, 1);
	gameGridLayout->addWidget(board, 0, 1, 1, 1);
	gameGridLayout->addLayout(chatLayout, 0, 2, 1, 1);

	layout->addLayout(topLayout);
	layout->addLayout(gameGridLayout);
	layout->addSpacing(200);
	layout->setAlignment(topLayout, Qt::AlignTop);
}

void GamePage::StyleElements()
{
	QFile styleFile("style.css");
	styleFile.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

void GamePage::SetSize()
{
	round->setReadOnly(true);
	time->setReadOnly(true);
	word->setReadOnly(true);
	chatHistory->setReadOnly(true);
	listPlayers->setReadOnly(true);
	messageInput->setFixedSize(300, 50);
	sendButton->setFixedSize(300, 50);
	listPlayers->setFixedSize(200, 450);
	round->setFixedSize(200, 50);
	time->setFixedSize(200, 50);
	word->setFixedSize(200, 50);
	chatHistory->setFixedSize(300, 350);
	messageInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sendButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	listPlayers->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	round->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	time->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	word->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	chatHistory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void GamePage::updateBoard(QMouseEvent* event)
{
	QPoint localPos = event->localPos().toPoint();
	int col = localPos.x() / 10;
	int row = localPos.y() / 10;

	if ((col >= 0 && col < 80) && (row >= 0 && row < 80))
	{
		board->drawingMatrix[row][col] = 1;
		board->update();
	}
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
		sendButton, chatHistory, board, gameGridLayout;
}