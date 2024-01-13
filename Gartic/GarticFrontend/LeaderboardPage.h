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
	void UpdateData();
	void showEvent(QShowEvent* event) override;
	void AddPlayer(const QString& playerName, const QString& playerScore);
	~LeaderboardPage();

private:
	QLabel* imageLabel, *title;
	QVBoxLayout* layout, *bottomLeftLayout, * middleLayout;
	QPushButton* returnButton;
	QHBoxLayout* topLeftLayout;
	bool isGameFinished = false;
	int index = 0;

	QVector<QString>* playerNames; 
	QVector<QString>* playerScores;

	QWidget* boardPadding;
	QVector<QWidget*> profilePaddings;
	QVector<QHBoxLayout*> profileLayouts;
	QVector<QLabel*> profileImages;
	QVector<QLabel*> profileScores;
	QVector<QLabel*> profileNames;
};
