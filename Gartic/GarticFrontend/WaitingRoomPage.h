#pragma once
#include <QtWidgets>
#include "PageController.h"

class WaitingRoomPage : public QWidget
{
	Q_OBJECT
public:

	enum class Difficulty : uint8_t
	{
		Easy,
		Medium,
		Hard,
		Ascending
	};

	WaitingRoomPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();

	void OnPlayerJoin(const QString& playerName);
	void UpdateMainPaddingSize(); //to be discussed

	int difficultyToInt(Difficulty difficulty);
	QString difficultyToQString(Difficulty difficulty);
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
	//QVector<QLabel*> profileNames;

	Difficulty currentDifficulty;


};

