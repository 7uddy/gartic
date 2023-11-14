#pragma once
#include "PageController.h"
#include <QtWidgets>
#include <QFile>

class MainMenuPage : public QWidget
{
	Q_OBJECT
public:
	MainMenuPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	void CreateButtonClicked();
	void JoinButtonClicked();
	~MainMenuPage();
private:
	QVBoxLayout* layout, *buttonsLayout;
	QHBoxLayout* topLayout;
	QLabel* imageLabel;
	QPushButton* createButton,*joinButton,* myProfile;
};

