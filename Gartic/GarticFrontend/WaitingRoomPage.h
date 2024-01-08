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
	void UpdateMainPaddingSize();
	void UpdateRoomCode(const std::string& codeLobby);

	int DifficultyToInt(Difficulty difficulty);
	QString DifficultyToQString(Difficulty difficulty);
	~WaitingRoomPage();

	void UpdateDataFromRoom();

private:
	QVBoxLayout* layout;
	QVBoxLayout* profilesLayout;
	QLabel* imageLabel;
	QPushButton* returnButton;
	QPushButton* startButton;
	QPushButton* code;
	QWidget* mainPadding;
	QPushButton* difficultyButton;
	QLabel* playersNumber;
	QLabel* statusText;
	QVector<QWidget*> profilePaddings;
	QVector<QHBoxLayout*> profileLayouts;
	//QVector<QLabel*> profileNames;

	Difficulty currentDifficulty;
	std::string roomCode;
	int statusRoom;
};

