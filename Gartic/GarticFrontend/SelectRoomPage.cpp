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

    connect(returnButton, &QPushButton::clicked, controller, [controller]() {
       controller->showPage("MainMenu");
   });
}

void SelectRoomPage::PlaceElements() {
    setLayout(layout);

    QHBoxLayout* topLeftLayout = new QHBoxLayout;
    QPixmap image("Images/Game_Name.png");
    imageLabel->setPixmap(image);
    topLeftLayout->addWidget(imageLabel);
    topLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QVBoxLayout* bottomLeftLayout = new QVBoxLayout;
    returnButton->setIconSize(QSize(50, 50));
    returnButton->setFixedSize(40, 40);
    bottomLeftLayout->addWidget(returnButton);
    bottomLeftLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    QVBoxLayout* middleLayout = new QVBoxLayout;
    middleLayout->addWidget(roomCode);
    middleLayout->addWidget(joinButton);
    middleLayout->setAlignment(Qt::AlignCenter);

    layout->addLayout(topLeftLayout);
    layout->addLayout(middleLayout);
    layout->addLayout(bottomLeftLayout);
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