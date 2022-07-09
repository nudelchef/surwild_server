#include "Player.h"

Player::Player() {
    handler = nullptr;
    textureString = "";

    tilePositionX = 0;
    tilePositionY = 0;
    x = 0;
    y = 0;
}

Player::Player(SocketHandler *handler_) {
    handler = handler_;
    textureString = "assets/naey_spritesheet.png";

    movementDirection = Direction::RIGHT;
    tilePositionX = 5;
    tilePositionY = 8;
    x = 5;
    y = 8;
}

Player::~Player() = default;

