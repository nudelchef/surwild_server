#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <arpa/inet.h> // htons ntohs

#include "Player.h"

class Player;

class PacketManager
{
public:

    struct PACKET{
        uint16_t packetId;

        PACKET() : packetId(0) {};
        PACKET(int id) : packetId(id) {};

        virtual std::string pack(){
            std::stringstream packet("");
            packet << htons(packetId);
            return packet.str();
        }
    };

    struct DISCONNECT : PACKET {
        DISCONNECT() : PACKET(1) {};
    };

    struct LOGIN : PACKET {
        std::string username;
        std::string password;

        LOGIN(std::string packet) : PACKET() {
            std::stringstream p_stream(packet);
            std::string line;

            // packetId will -always- be 2
            std::getline(p_stream, line, '\037');
            packetId = ntohs((uint16_t) std::stoul(line));

            std::getline(p_stream, username, '\037');
            std::getline(p_stream, password, '\037');
        };
        LOGIN(std::string username_, std::string password_) : PACKET(2) {
            username = username_;
            password = password_;
        };

        std::string pack(){
            std::stringstream packet("");
            packet    << htons(packetId)
            << '\037' << username
            << '\037' << password
            ;
            return packet.str();
        }
    };

    struct UNREGISTER_PLAYER : PACKET {
        unsigned int playerId;

        UNREGISTER_PLAYER(std::string packet) : PACKET() {
            std::stringstream p_stream(packet);
            std::string line;

            // packetId will -always- be 3
            std::getline(p_stream, line, '\037');
            packetId = ntohs((uint16_t) std::stoul(line));

            std::getline(p_stream, line, '\037');
            playerId = ntohs((unsigned int) std::stoul(line));
        };
        UNREGISTER_PLAYER(Player* player) : PACKET(3) {
            playerId = player->playerId;
        };

        std::string pack(){
            std::stringstream packet("");
            packet    << htons(packetId)
            << '\037' << htons(playerId);
            ;
            return packet.str();
        }
    };

    struct PLAYER_DATA : PACKET {
        unsigned int playerId;
        unsigned int entityId;


        std::string texture;

        Direction movementDirection;
        unsigned short tilePositionX;
        unsigned short tilePositionY;

        unsigned short x;
        unsigned short y;


        PLAYER_DATA(std::string packet) : PACKET() {
            std::stringstream p_stream(packet);
            std::string line;

            // packetId will -always- be 4
            std::getline(p_stream, line, '\037');
            packetId = ntohs((uint16_t) std::stoul(line));

            std::getline(p_stream, line, '\037');
            playerId = ntohs((unsigned int) std::stoul(line));

            std::getline(p_stream, line, '\037');
            entityId = ntohs((unsigned int) std::stoul(line));

            std::getline(p_stream, texture, '\037');

            std::getline(p_stream, line, '\037');
            movementDirection = Direction(ntohs((unsigned short) std::stoul(line)));

            std::getline(p_stream, line, '\037');
            tilePositionX = ntohs((unsigned short) std::stoul(line));

            std::getline(p_stream, line, '\037');
            tilePositionY = ntohs((unsigned short) std::stoul(line));

            std::getline(p_stream, line, '\037');
            x = ntohs((unsigned short) std::stoul(line));

            std::getline(p_stream, line, '\037');
            y = ntohs((unsigned short) std::stoul(line));


            // debug
            std::cout << "\\ ID: " << packetId << std::endl;
            std::cout << "\\ playerId: " << playerId << std::endl;
            std::cout << "\\ entityId: " << entityId << std::endl;
            std::cout << "\\ texture: " << texture << std::endl;
            std::cout << "\\ movementDirection: " << movementDirection << std::endl;
            std::cout << "\\ tilePositionX: " << tilePositionX << std::endl;
            std::cout << "\\ tilePositionY: " << tilePositionY << std::endl;
            std::cout << "\\ x: " << x << std::endl;
            std::cout << "\\ y: " << y << std::endl;

        };
        PLAYER_DATA(Player* player) : PACKET(4) {
            playerId = player->playerId;
            entityId = player->entityId;
            texture = player->texture;
            movementDirection = player->movementDirection;
            tilePositionX = player->tilePositionX;
            tilePositionY = player->tilePositionY;
            x = player->x;
            y = player->y;
        };

        std::string pack(){
            std::stringstream packet("");
            packet    << htons(packetId)
            << '\037' << htons(playerId)
            << '\037' << htons(entityId)
            << '\037' << texture
            << '\037' << htons(movementDirection)
            << '\037' << htons(tilePositionX)
            << '\037' << htons(tilePositionY)
            << '\037' << htons(x)
            << '\037' << htons(y)
            ;
            return packet.str();
        }
    };

protected:
private:
};

#endif // PACKETMANAGER_H
