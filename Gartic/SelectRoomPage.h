#pragma once
#include <QFile>
#include <QtWidgets>
#include "PageController.h"

class SelectRoomPage : public QWidget
{
    Q_OBJECT

public:
    SelectRoomPage(PageController* controller, QWidget* parent = nullptr);
    void PlaceElements();
    void StyleElements();
    void SetSize();
    void JoinButtonClicked();

private:
    QLineEdit* roomCode;
    QPushButton* joinButton;
    QLabel* imageLabel;
    QVBoxLayout* layout;
    QPushButton* returnButton;
};