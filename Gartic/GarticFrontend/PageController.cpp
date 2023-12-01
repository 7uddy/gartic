#include "PageController.h"

PageController::PageController(QWidget* parent):QStackedWidget(parent)
{
	/*empty*/
}

void PageController::addPage(QWidget* page, const QString& name)
{
	pagesMap[name] = page;
	QStackedWidget::addWidget(page);
}

void PageController::showPage(const QString& name)
{
	if (pagesMap.contains(name))
	{
		QWidget* page = pagesMap[name];
		setCurrentWidget(page);
	}
}

void PageController::setStartupPage(const QString& name)
{
	if (pagesMap.contains(name))
	{
		showPage(name);
	}
}

bool PageController::verifyLogin(const QString& enteredUsername, const QString& enteredPassword)
{
	QString expectedPassword = "password"; //test
	QString expectedUsername = "user"; //test
	if (enteredUsername == expectedUsername && enteredPassword == expectedPassword)
	{
		return true;
	}
	return false;
}

bool PageController::verifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword)
{
	if ((enteredUsername == "user") || (enteredEmail == "user@yahoo.com") || (enteredPassword == "password")) // test
	{
		return false;
	}
	return true;
}