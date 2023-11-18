#pragma once
#include <QtWidgets>
#include "PageController.h"

class GamePage : public QWidget
{
	Q_OBJECT
public:
	GamePage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	~GamePage();
private:
	QLabel* imageLabel;
	QTextEdit* listPlayers, * round, * time, * word;
};

