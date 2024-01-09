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
	/*void OnPlayerLeave(const int& index);*/
	void UpdateMainPaddingSize();
	void UpdateRoomCode(const std::string& codeLobby, const bool& owner);

	int DifficultyToInt(Difficulty difficulty);
	QString DifficultyToQString(Difficulty difficulty);
	~WaitingRoomPage();

private slots:
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
	QVector<QLabel*> profileNames;
	QTimer* timer;

	Difficulty currentDifficulty;
	std::string roomCode;
	int statusRoom;
	Player player;
	bool ownerRoom;
	std::vector<std::string> oldPlayers;
};

