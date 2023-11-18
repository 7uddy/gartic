#pragma once
#include <QtWidgets>
#include "PageController.h"

class WaitingRoomPage : public QWidget
{
	Q_OBJECT
public:
	WaitingRoomPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	~WaitingRoomPage();
private:
	QPushButton* startButton,*easyButton,*mediumButton,*hardButton;
	QLabel* imageLabel;
	QHBoxLayout* topLayout,*roomInfo;
	QVBoxLayout* layout, *playersInfo,*infoGame;
	QTextEdit* listPlayers,*status,*playersNumber,* roomCode,* difficulty;
};

