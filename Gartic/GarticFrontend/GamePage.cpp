#include "GamePage.h"

GamePage::GamePage(PageController* controller, QWidget* parent)
{
	listPlayers = new QTextEdit("Players:", this);
	round = new QTextEdit("Round: ?/4", this);
	time = new QTextEdit("Time: ???", this);
	word = new QTextEdit("????", this);
	imageLabel = new QLabel(this);
}

void GamePage::PlaceElements()
{
	/*empty*/
}

void GamePage::StyleElements()
{
	/*empty*/
}

void GamePage::SetSize()
{
	/*empty*/
}

GamePage::~GamePage()
{
	delete imageLabel, listPlayers, round, time, word;
}
