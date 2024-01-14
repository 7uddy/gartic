#pragma once
#include <QFile>
#include <QtWidgets>
#include "PageController.h"
#include "SharedUIElements.h"

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
    QPushButton* joinButton;
    QVBoxLayout* layout,* bottomLeftLayout,* middleLayout;
    QHBoxLayout* topLeftLayout;
    SharedUIElements sharedElements;
};