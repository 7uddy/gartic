#include "GamePage.h"

GamePage::GamePage(PageController* controller, QWidget* parent) : drawingMatrix(numRows, std::vector<int>(numCols, 0))
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
	SetSize();
	StyleElements();
	PlaceElements();
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
	topLayout->addSpacing(100);

	chatLayout->addWidget(chatHistory);
	chatLayout->addWidget(messageInput);
	chatLayout->addWidget(sendButton);

	gameLayout->addSpacing(100);
	gameLayout->addWidget(listPlayers);
	gameLayout->setAlignment(listPlayers, Qt::AlignLeft | Qt::AlignCenter);
	gameLayout->addLayout(chatLayout);
	gameLayout->addSpacing(100);
	gameLayout->setAlignment(chatLayout, Qt::AlignRight | Qt::AlignBottom);

	layout->addLayout(topLayout);
	layout->addLayout(gameLayout);
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
	listPlayers->setFixedSize(200,450);
	round->setFixedSize(200, 50);
	time->setFixedSize(200, 50);
	word->setFixedSize(200, 50);
	chatHistory->setFixedSize(300,350);
	messageInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sendButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	listPlayers->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	round->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	time->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	word->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	chatHistory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void GamePage::paintEvent(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setRenderHint(QPainter::Antialiasing, true);
	const int matrixWidth = numCols * 10;
	const int matrixHeight = numRows * 10;
	int startX = (width() - matrixWidth) / 2;
	int startY = (height() - matrixHeight) / 2;
	for(int index=0;index<numRows;index++)
		for (int jndex = 0; jndex < numCols; jndex++)
		{
			QRect rectangle(startX + jndex * 10, startY + index * 10, 10, 10);
			if (drawingMatrix[index][jndex] == 0)
			{
				paint.setPen(QPen(Qt::white, 0));
				paint.setBrush(Qt::white);
				paint.drawRect(rectangle);
			}
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
		sendButton, chatHistory;
}
