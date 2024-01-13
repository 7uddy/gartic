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
	void UpdateBoard(QMouseEvent* event);
	void SetDrawMode();
	void SetEraseMode();
	void showEvent(QShowEvent* event) override;
	~GamePage();
private slots:
	void SendMessage();
	void UpdateDataFromGame();
private:
	QLabel* imageLabel;
	QTextEdit* listPlayers, * round, * time, * word, * chatHistory;
	QHBoxLayout* topLayout, * gameLayout,* buttonsLayout;
	QVBoxLayout* layout, * chatLayout;
	QLineEdit* messageInput;
	QPushButton* sendButton, *drawButton, *eraseButton;
	BoardWidget* board;
	QGridLayout* gameGridLayout;

	bool currentMode = true;
	QTimer* timer;
	Player player;
	PageController* m_controller;
	bool painter;
	bool isGameStarted = false;
};
