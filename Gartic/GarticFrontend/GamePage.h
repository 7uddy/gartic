#pragma once
#include <QtWidgets>
#include "PageController.h"
#include <vector>
#include <QMouseEvent>
#include "BoardWidget.h"

class GamePage : public QWidget
{
	Q_OBJECT
public:
	GamePage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	void UpdateBoardDraw(QMouseEvent* event);
	void SetDrawMode();
	void SetEraseMode();
	void showEvent(QShowEvent* event) override;
	~GamePage();

private slots:
	void SendMessage();
	void UpdateBoard();
	void UpdateTimer();
	void UpdateRound();
	bool UpdateStatus();
	void UpdatePlayers();
	void UpdateChat();
	void UpdateWord();
	void UpdateDataFromGame();
private:
	QLabel* imageLabel, * round, * time, * word;
	QTextEdit* listPlayers, * chatHistory;
	QHBoxLayout* topLayout, * gameLayout,* buttonsLayout;
	QVBoxLayout* layout, * chatLayout;
	QLineEdit* messageInput;
	QPushButton* sendButton, *drawButton, *eraseButton;
	BoardWidget* board;
	QGridLayout* gameGridLayout;

	bool currentMode;
	QTimer* timer;
	Player player;
	PageController* m_controller;
	bool painter;
	bool isGameStarted;
	int previousTime;
};
