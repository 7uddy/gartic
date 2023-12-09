#include "PageController.h"

PageController::PageController(QWidget* parent):QStackedWidget(parent)
{
	/*empty*/
}

void PageController::AddPage(QWidget* page, const QString& name)
{
	pagesMap[name] = page;
	QStackedWidget::addWidget(page);
}

void PageController::ShowPage(const QString& name)
{
	if (pagesMap.contains(name))
	{
		QWidget* page = pagesMap[name];
		setCurrentWidget(page);
	}
}

void PageController::SetStartupPage(const QString& name)
{
	if (pagesMap.contains(name))
	{
		ShowPage(name);
	}
}

bool PageController::VerifyLogin(const QString& enteredUsername, const QString& enteredPassword)
{
	return player.VerifyLogin(enteredUsername.toStdString(), enteredPassword.toStdString());
}

bool PageController::VerifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword)
{
	return player.VerifyRegister(enteredUsername.toStdString(), enteredEmail.toStdString(), enteredPassword.toStdString());
}