#pragma once
#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include "PageController.h"

class SharedUIElements : public QWidget
{
	Q_OBJECT

public:

	SharedUIElements();
	void StyleElements();
	QPushButton* GetReturnButton();
	QLabel* GetImageLabel();
	~SharedUIElements();

private:
	 QLabel* imageLabel;
	 QPushButton* returnButton;
};
