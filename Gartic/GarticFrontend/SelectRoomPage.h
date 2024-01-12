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
    ~SelectRoomPage();

private:
    QLineEdit* roomCode;
    QPushButton* joinButton, * returnButton;
    QLabel* imageLabel;
    QVBoxLayout* layout,* bottomLeftLayout,* middleLayout;
    QHBoxLayout* topLeftLayout;
};