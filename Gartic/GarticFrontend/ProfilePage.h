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
	~ProfilePage();
private:
	QVBoxLayout* layout,*infoLayout;
	QHBoxLayout* topLayout, *buttonLayout;
	QLabel* imageLabel;
	QTextEdit* username, * averageScore,* matchHistory;
	QPushButton* returnButton;
};

