#include "ProfilePage.h"

ProfilePage::ProfilePage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	username = new QTextEdit("Username", this);
	averageScore = new QTextEdit("Average Score", this);
	matchHistory = new QTextEdit("Match History", this);
	SetSize();
	StyleElements();
	PlaceElements();
}

void ProfilePage::PlaceElements()
{
	
}

void ProfilePage::StyleElements()
{
	username->setReadOnly(true);
	averageScore->setReadOnly(true);
	matchHistory->setReadOnly(true);
}

void ProfilePage::SetSize()
{
	
}
