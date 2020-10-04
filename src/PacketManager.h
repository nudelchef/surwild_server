#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <arpa/inet.h> // htons ntohs

#include "Direction.h"

class Player;

namespace PACKET {
    struct PACKET {
    public:
        uint16_t packetId;

        PACKET();
        PACKET(int id);

        virtual std::string pack();
    };

    struct DISCONNECT : PACKET {
    public:
        DISCONNECT();
    };

    struct LOGIN : PACKET {
    public:
        std::string username;
        std::string password;

        LOGIN(std::string packet);
        LOGIN(std::string username_, std::string password_);

        std::string pack();
    };

    struct UNREGISTER_PLAYER : PACKET {
    public:
        uint32_t playerId;

        UNREGISTER_PLAYER(std::string packet);
        UNREGISTER_PLAYER(Player* player);

        std::string pack();
    };

    struct REGISTER_PLAYER : PACKET {
    public:
        uint32_t playerId;
        uint32_t entityId;


        std::string textureString;

        Direction movementDirection;
        uint32_t tilePositionX;
        uint32_t tilePositionY;

        uint32_t x;
        uint32_t y;


        REGISTER_PLAYER(std::string packet);
        REGISTER_PLAYER(Player* player);

        std::string pack();
    };
}

#endif // PACKETMANAGER_H
