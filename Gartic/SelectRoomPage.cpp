#include "SelectRoomPage.h"

SelectRoomPage::SelectRoomPage(PageController* controller, QWidget* parent)
{
    roomCode = new QLineEdit(this);
    joinButton = new QPushButton("Join Room", this);
    imageLabel = new QLabel(this);
    layout = new QVBoxLayout(this);

    SetSize();
    StyleElements();
    PlaceElements();
}

void SelectRoomPage::PlaceElements() {
    setLayout(layout);
    QHBoxLayout* innerLayout = new QHBoxLayout;
    QPixmap image("Images/Game_Name.png");
    imageLabel->setPixmap(image);
    innerLayout->addWidget(imageLabel);
    innerLayout->setContentsMargins(55, 0, 0, 70);
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
    setStyleSheet(styleSheet);
}

void SelectRoomPage::SetSize() {
    roomCode->setFixedSize(200, 50);
    joinButton->setFixedSize(200, 50);
    roomCode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    joinButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void SelectRoomPage::JoinButtonClicked()
{
    /*Empty*/
}