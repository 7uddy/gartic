#pragma once
#include <QtWidgets>
#include "PageController.h"

class ProfilePage:public QWidget
{
	Q_OBJECT
public:
	ProfilePage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
private:
	QVBoxLayout* layout;
	QLabel* imageLabel;
	QTextEdit* username;
	QTextEdit* averageScore;
	QTextEdit* matchHistory;
};

