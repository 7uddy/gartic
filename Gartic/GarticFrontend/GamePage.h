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
	~GamePage();
private slots:
	void SendMessage();
private:
	QLabel* imageLabel;
	QTextEdit* listPlayers, * round, * time, * word, * chatHistory;
	QHBoxLayout* topLayout, * gameLayout;
	QVBoxLayout* layout, * chatLayout;
	QLineEdit* messageInput;
	QPushButton* sendButton;
	BoardWidget* board;
	QGridLayout* gameGridLayout;
};
