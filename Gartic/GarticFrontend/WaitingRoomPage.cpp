#include "WaitingRoomPage.h"

WaitingRoomPage::WaitingRoomPage(PageController* controller, QWidget* parent)
{
	startButton = new QPushButton("Start",this);
	easyButton = new QPushButton("Easy",this);
	mediumButton = new QPushButton("Medium",this);
	hardButton = new QPushButton("Hard",this);
	imageLabel = new QLabel(this);
}

void WaitingRoomPage::PlaceElements()
{
	/*empty*/
}

void WaitingRoomPage::StyleElements()
{
	/*empty*/
}

void WaitingRoomPage::SetSize()
{
	/*empty*/
}

WaitingRoomPage::~WaitingRoomPage()
{
	delete startButton, easyButton, mediumButton, hardButton, imageLabel;
}

