#pragma once
#include <QtWidgets>
#include <iterator>
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
	void SetConnections();

	void OnPlayerJoin(const QString& playerName);
	void UpdateMainPaddingSize();
	void UpdateRoomCode(const std::string& codeLobby, const bool& owner);
	void ClearPlayerProfiles();
	void OnPlayerLeave(int index);
	void ClearPlayerProfile(int index);

	int DifficultyToInt(const Difficulty& difficulty);
	QString DifficultyToQString(const Difficulty& difficulty);
	~WaitingRoomPage();

private slots:
	void UpdateDataFromRoom();

private:
	QVBoxLayout* layout, * profilesLayout, * bottomLeftLayout, * roomSettingLayout;
	QHBoxLayout* topLeftLayout,* statusLayout;
	QLabel* imageLabel, * playersNumber, * statusText, *difficulty,* roomCode;
	QPushButton* returnButton,* startButton,* code, * difficultyButton;
	QWidget* mainPadding;
	QGridLayout* middleLayout,*mainPaddingLayout;
	QVector<QWidget*> profilePaddings;
	QVector<QHBoxLayout*> profileLayouts;
	QVector<QLabel*> profileNames;

	QTimer* timer;
	Difficulty currentDifficulty;
	std::string codeRoom;
	int statusRoom;
	Player player;
	bool ownerRoom;
	std::vector<std::string> oldPlayers;
	PageController* m_controller;
};

