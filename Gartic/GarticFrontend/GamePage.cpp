#include "GamePage.h"

GamePage::GamePage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	topLayout = new QHBoxLayout();
	listPlayers = new QTextEdit("Players:", this);
	round = new QTextEdit(this);
	time = new QTextEdit(this);
	word = new QTextEdit(this);
	chatLayout = new QVBoxLayout();
	messageInput = new QLineEdit(this);
	sendButton = new QPushButton("Send", this);
	chatHistory = new QTextEdit(this);
	gameLayout = new QHBoxLayout();
	buttonsLayout = new QHBoxLayout();
	board = new BoardWidget();
	gameGridLayout = new QGridLayout();
	drawButton = new QPushButton("Draw", this);
	eraseButton = new QPushButton("Erase", this);
	timer = new QTimer(this);
	m_controller = controller;
	SetSize();
	StyleElements();
	PlaceElements();
	connect(sendButton, &QPushButton::clicked, this, &GamePage::SendMessage);
	connect(board, &BoardWidget::MouseDraw, this, &GamePage::UpdateBoard);
	connect(drawButton, &QPushButton::clicked, this, &GamePage::SetDrawMode);
	connect(eraseButton, &QPushButton::clicked, this, &GamePage::SetEraseMode);
	connect(timer, &QTimer::timeout, this, &GamePage::UpdateDataFromGame);
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
	gameGridLayout->addWidget(board, 0, 1, 3, 2);
	gameGridLayout->addWidget(drawButton, 3, 1, 1, 1);
	gameGridLayout->addWidget(eraseButton, 3, 2, 1, 1);
	gameGridLayout->addLayout(chatLayout, 0, 3, 1, 1);

	layout->addLayout(topLayout);
	layout->addLayout(gameGridLayout);
	layout->setAlignment(topLayout, Qt::AlignTop);
	layout->addSpacing(100);
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
	drawButton->setFixedSize(300, 50);
	eraseButton->setFixedSize(300, 50);
	chatHistory->setFixedSize(300, 350);

	messageInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sendButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	listPlayers->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	round->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	time->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	word->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	chatHistory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	drawButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	eraseButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void GamePage::UpdateBoard(QMouseEvent* event)
{
	if (painter)
	{
		QPoint localPos = event->localPos().toPoint();
		int col = localPos.x() / 10;
		int row = localPos.y() / 10;
		if ((col >= 0 && col < board->GetNumCols()) && (row >= 0 && row < board->GetNumRows()))
		{
			if(currentMode)
			    board->pointsCoordinates.push_back({ row, col });
			else
			{
				auto it = std::find(board->pointsCoordinates.begin(), board->pointsCoordinates.end(), std::make_pair(row, col));
				if (it != board->pointsCoordinates.end())
				{
					board->pointsCoordinates.erase(it);
				}
			}
			board->update();
		}
	}
}

void GamePage::SetDrawMode()
{
	currentMode = true;
}

void GamePage::SetEraseMode()
{
	currentMode = false;
}

void GamePage::showEvent(QShowEvent* event)
{
	player = m_controller->GetPlayer();
	QMessageBox::StandardButton reply;
	reply = QMessageBox::information(this, "Game", "The game has begun.", QMessageBox::Ok);
	if (reply == QMessageBox::Ok)
	{
		UpdateDataFromGame();
	}
	QWidget::showEvent(event);
}

void GamePage::UpdateDataFromGame()
{
	auto responseTimer = cpr::Get(
		cpr::Url{ "http://localhost:18080/gettimer" });
	if(responseTimer.text=="0")
	{ 
		messageInput->setEnabled(true);
	}
	int difference = 60 - std::stoul(responseTimer.text);
	time->setText("Time:" + QString::number(difference));

	auto responseRound = cpr::Get(
		cpr::Url{ "http://localhost:18080/getroundnumber" });
	round->setText("Round: " + QString::fromUtf8(responseRound.text.c_str()) + "/4");

	auto responsePlayers = cpr::Get(
		cpr::Url{ "http://localhost:18080/getplayersdatafromgame" });
	auto players = nlohmann::json::parse(responsePlayers.text);
	listPlayers->clear();
	std::string playerInfo,playerScore;
	bool isFirst = true;
	for(const auto& jsonEntry: players)
	{
		if (jsonEntry.find("username") != jsonEntry.end())
		{
			playerInfo = jsonEntry["username"];
		}
		if (jsonEntry.find("score") != jsonEntry.end())
		{
			if (isFirst)
			{
				if (playerInfo == player.GetUsername())
					painter = true;
				else
					painter = false;
				isFirst = false;
			}
			playerScore = jsonEntry["score"];
			playerInfo = playerInfo +"     "+ playerScore.substr(0, playerScore.find('.') + 3);;
			listPlayers->append(QString::fromUtf8(playerInfo));
		}
	}

	auto responseChat = cpr::Get(
		cpr::Url{ "http://localhost:18080/getchat" },
		cpr::Parameters{
			{ "username", player.GetUsername()},
		});
	auto chat = nlohmann::json::parse(responseChat.text);
	if(!chat.empty())
	{
		chatHistory->clear();
		for (const auto& jsonEntry : chat)
		{
			if (jsonEntry.find("message") != jsonEntry.end())
			{
				std::string messageText = jsonEntry["message"];
				chatHistory->append(QString::fromUtf8(messageText));
			}
		}
	}

	if (painter)
	{
		messageInput->setEnabled(false);
		std::string boardInput = board->GetBoard();
		qDebug() << boardInput.size() << "\n";
		auto responseBoard = cpr::Get(
			cpr::Url{ "http://localhost:18080/sendboard" },
			cpr::Parameters{
					{ "board",  boardInput},
			}
		);
	}
	else
	{
		auto responseBoard = cpr::Get(
			cpr::Url{ "http://localhost:18080/getboard" }
		);
		auto boardOutput = nlohmann::json::parse(responseBoard.text);
		std::string boardText = boardOutput["board"].get<std::string>();
		board->SetBoard(boardText);
	}

	auto responseWord = cpr::Get(
		cpr::Url{ "http://localhost:18080/getword" },
		cpr::Parameters{
					{ "username", player.GetUsername()},
		}
	);
	auto wordJson= nlohmann::json::parse(responseWord.text);
	std::string wordText = wordJson["Word"].get<std::string>();
	std::string spacedWordText;
	for (char character : wordText) 
	{
		spacedWordText += character;
		spacedWordText += ' ';
	}
	word->setText(QString::fromUtf8(spacedWordText));

	timer->start(500);
}

void GamePage::SendMessage()
{
	QString message = messageInput->text();
	if (!message.isEmpty())
	{
		std::string messageText = message.toUtf8().constData();
		auto responseChat = cpr::Get(
			cpr::Url{ "http://localhost:18080/addmessagetochat" },
			cpr::Parameters{
				{ "username", player.GetUsername()},
				{"message", messageText},
			});
		messageInput->clear();
		if (responseChat.status_code == 200)
			qDebug() << "The message was sent with success.";
		else if (responseChat.status_code == 201)
		{
			messageInput->setEnabled(false);
			qDebug() << "The player guessed the word.";
		}
		else
			qDebug() << "The message was not sent with success.";
	}
}

GamePage::~GamePage()
{
	/*empty*/
}