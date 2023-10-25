#include "PageController.h"

PageController::PageController(QWidget* parent):QStackedWidget(parent)
{
}

void PageController::addPage(QWidget* page)
{
	addWidget(page);
}

void PageController::showPage(int index)
{
	setCurrentIndex(index);
}
