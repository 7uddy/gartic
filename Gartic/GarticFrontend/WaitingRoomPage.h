#pragma once
#include <QtWidgets>
#include "PageController.h"

class WaitingRoomPage : public QWidget
{
	Q_OBJECT
public:
	WaitingRoomPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	void OnPlayerJoin(const QString& playerName);
	void UpdateMainPaddingSize();

	~WaitingRoomPage();
private:
	QVBoxLayout* layout;
	QVBoxLayout* profilesLayout;
	QLabel* imageLabel;
	QPushButton* returnButton;
	QPushButton* startButton;

	QWidget* mainPadding;
	QPushButton* difficultyButton;
	QLabel* playersNumber;

	QVector<QWidget*> profilePaddings;
	QVector<QHBoxLayout*> profileLayouts;


};

