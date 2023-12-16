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
    QVBoxLayout* layout;
    QLabel* imageLabel;
    QPushButton* returnButton;

    QWidget* mainPadding;
    QLabel* username;
    QLabel* userImage;
    QLabel* averageScore;
    QTextEdit* matchHistory;
};

