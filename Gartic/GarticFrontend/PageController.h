#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QMessageBox>

class PageController:public QStackedWidget
{
public:
	PageController(QWidget* parent = nullptr);
	void addPage(QWidget *page, const QString& name);
	void showPage(const QString& name);
	void setStartupPage(const QString& name);
	bool verifyLogin(const QString& enteredUsername, const QString& enteredPassword);
	bool verifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword);
private:
	QMap<QString, QWidget*> pagesMap;
};

