#include "ProfilePage.h"

ProfilePage::ProfilePage(PageController* controller, QWidget* parent)
{
	imageLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	username = new QTextEdit("Username", this);
	username->setReadOnly(true);
	averageScore = new QTextEdit("Average Score", this);
	averageScore->setReadOnly(true);
	matchHistory = new QTextEdit("Match History", this);
	matchHistory->setReadOnly(true);
}

void ProfilePage::PlaceElements()
{
}

void ProfilePage::StyleElements()
{
}

void ProfilePage::SetSize()
{
}
