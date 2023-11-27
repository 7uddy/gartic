#pragma once
#include <QFile>
#include <QtWidgets>
#include "PageController.h"

class LeaderboardPage  : public QWidget
{
	Q_OBJECT

public:
	LeaderboardPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void SetSize();
	void OnPlayerJoin(const QString& playerName, const QString& playerScore); //to be renamed
	~LeaderboardPage();

private:
	QLabel* imageLabel;
	QVBoxLayout* layout;
	QPushButton* returnButton;

	//FOR TESTING
	QVector<QString>* playerNames; 
	QVector<QString>* playerScores;
	QPushButton* testButton;
	uint16_t index;
	//FOR TESTING

	QWidget* boardPadding;
	QVector<QWidget*> profilePaddings;
	QVector<QHBoxLayout*> profileLayouts;
	QVector<QLabel*> profileImages;
	QVector<QLabel*> profileScores;
	QVector<QLabel*> profileNames;
};
