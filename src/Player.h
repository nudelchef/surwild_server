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

        unsigned int playerId;

    protected:

    private:
        SocketHandler* handler;
};

#endif // PLAYER_H
