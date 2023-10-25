#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>

class PageController:public QStackedWidget
{
public:
	PageController(QWidget* parent = nullptr);
	void addPage(QWidget *page);
	void showPage(int index);
};

