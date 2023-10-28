#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>

class PageController:public QStackedWidget
{
public:
	PageController(QWidget* parent = nullptr);
	void addPage(QWidget *page, const QString& name);
	void showPage(const QString& name);
	void setStartupPage(const QString& name);
private:
	QMap<QString, QWidget*> pagesMap;
};

