#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class SocketHandler;

class Player : public Entity {
public:
    Player();

    explicit Player(SocketHandler *handler_);

    ~Player() override;

    uint32_t playerId{};

protected:

private:
    SocketHandler *handler;
};

#endif // PLAYER_H
