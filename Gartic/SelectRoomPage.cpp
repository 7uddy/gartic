#include "SelectRoomPage.h"

void SelectRoomPage::SetSize() {
    roomCode->setFixedSize(200, 50);
    joinButton->setFixedSize(200, 50);
    roomCode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    joinButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
