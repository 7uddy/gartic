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
