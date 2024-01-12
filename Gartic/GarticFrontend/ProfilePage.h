#pragma once
#include <QtWidgets>
#include <algorithm> 
#include <numeric> 
#include "PageController.h"

class ProfilePage:public QWidget
{
	Q_OBJECT
public:
	ProfilePage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
    void UpdateData();
    void showEvent(QShowEvent* event) override;
	~ProfilePage();
private:
    QVBoxLayout* layout, * bottomLeftLayout, * middleLayout, * leftSideLayout;
    QPushButton* returnButton;
    QHBoxLayout* topLeftLayout, * mainPaddingLayout;
    QWidget* mainPadding;
    QLabel* username, * userImage, * averageScore,* imageLabel;;
    QTextEdit* matchHistory;
    Player player;
    PageController* m_controller;
};

