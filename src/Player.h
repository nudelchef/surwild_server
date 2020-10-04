#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class SocketHandler;

class Player: public Entity
{
    public:
        Player();
        Player(SocketHandler* handler_);
        virtual ~Player();

        uint32_t playerId;

    protected:

    private:
        SocketHandler* handler;
};

#endif // PLAYER_H
