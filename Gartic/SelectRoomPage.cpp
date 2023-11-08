#include "SelectRoomPage.h"

SelectRoomPage::SelectRoomPage(PageController* controller, QWidget* parent)
{
    roomCode = new QLineEdit(this);
    joinButton = new QPushButton("Join Room", this);
    imageLabel = new QLabel(this);
    layout = new QVBoxLayout(this);
    returnButton = new QPushButton(this);

    SetSize();
    StyleElements();
    PlaceElements();
}

void SelectRoomPage::PlaceElements() {
    setLayout(layout);

    QHBoxLayout* topLeftLayout = new QHBoxLayout;
    QPixmap image("Images/Game_Name.png");
    imageLabel->setPixmap(image);
    topLeftLayout->addWidget(imageLabel);
    topLeftLayout->setContentsMargins(55, 0, 0, 70);
    topLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->setContentsMargins(400, 100, 400, 100);
    layout->addWidget(roomCode);
    layout->addWidget(joinButton);
    layout->setAlignment(Qt::AlignCenter);
}

void SelectRoomPage::StyleElements() {
    roomCode->setPlaceholderText("Room Code");
    QFile styleFile("style.css");
    styleFile.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = styleFile.readAll();
    returnButton->setAccessibleName("returnButton");
    setStyleSheet(styleSheet);
}

void SelectRoomPage::SetSize() {
    roomCode->setFixedSize(200, 50);
    joinButton->setFixedSize(200, 50);
    roomCode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    joinButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void SelectRoomPage::JoinButtonClicked()
{
    /*Empty*/
}