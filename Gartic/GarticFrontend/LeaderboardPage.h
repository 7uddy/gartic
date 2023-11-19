#pragma once
#include <QFile>
#include <QtWidgets>
#include "PageController.h"

class LeaderboardPage  : public QWidget
{
	Q_OBJECT

public:
	LeaderboardPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	~LeaderboardPage();

private:
	QLabel* imageLabel;
	QVBoxLayout* layout;
	QPushButton* returnButton;
};
