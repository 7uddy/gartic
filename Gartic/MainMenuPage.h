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
private:
	QVBoxLayout* layout;
	QLabel* imageLabel;
	QPushButton* createButton;
	QPushButton* joinButton;
	QPushButton* myProfile;
};

