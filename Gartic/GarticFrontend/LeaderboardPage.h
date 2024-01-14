#pragma once
#include <QFile>
#include <QtWidgets>
#include "PageController.h"
#include "SharedUIElements.h"

class LeaderboardPage  : public QWidget
{
	Q_OBJECT

public:
	LeaderboardPage(PageController* controller, QWidget* parent = nullptr);
	void PlaceElements();
	void StyleElements();
	void UpdateData();
	void showEvent(QShowEvent* event) override;
	void AddPlayer(const QString& playerName, const QString& playerScore);
	void ClearPlayerProfiles();
	~LeaderboardPage();

private:
	QLabel*title;
	QVBoxLayout* layout, *bottomLeftLayout, * middleLayout;
	QHBoxLayout* topLeftLayout;
	SharedUIElements sharedElements;
	bool isGameFinished;
	int index;

	QVector<QString>* playerNames; 
	QVector<QString>* playerScores;

	QWidget* boardPadding;
	QVector<QWidget*> profilePaddings;
	QVector<QHBoxLayout*> profileLayouts;
	QVector<QLabel*> profileImages;
	QVector<QLabel*> profileScores;
	QVector<QLabel*> profileNames;
};
