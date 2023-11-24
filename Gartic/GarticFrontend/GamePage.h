#pragma once
#include <QtWidgets>
#include "PageController.h"
#include <vector>
#include <QMouseEvent>

class GamePage : public QWidget
{
	Q_OBJECT
public:
	GamePage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	virtual void paintEvent(QPaintEvent* event);
	~GamePage();
private slots:
	void SendMessage();
private:
	QLabel* imageLabel;
	QTextEdit* listPlayers, * round, * time, * word, *chatHistory;
	QHBoxLayout *topLayout,*gameLayout;
	QVBoxLayout* layout, * chatLayout;
	QLineEdit* messageInput; 
	QPushButton* sendButton;
	const int numRows = 50;
	const int numCols = 80;
	std::vector<std::vector<int>> drawingMatrix;
};
