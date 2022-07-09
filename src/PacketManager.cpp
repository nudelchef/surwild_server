#include "PacketManager.h"

#include "Player.h"

namespace PACKET {

    //// packet
    PACKET::PACKET() : packetId(0) {};

    PACKET::PACKET(int id) : packetId(id) {};

    std::string PACKET::PACKET::pack() {
        std::stringstream packet("");
        packet << htons(packetId);
        return packet.str();
    }

    DISCONNECT::DISCONNECT() : PACKET(1) {};


    //// login
    LOGIN::LOGIN(std::string packet) : PACKET() {
        std::stringstream p_stream(packet);
        std::string line;

        // packetId will -always- be 2
        std::getline(p_stream, line, '\037');
        packetId = ntohs(static_cast<uint16_t>(std::stoul(line)));

        std::getline(p_stream, username, '\037');
        std::getline(p_stream, password, '\037');
    }

    LOGIN::LOGIN(std::string username_, std::string password_) : PACKET(2) {
        username = username_;
        password = password_;
    }

    std::string LOGIN::LOGIN::pack() {
        std::stringstream packet("");
        packet << htons(packetId)
               << '\037' << username
               << '\037' << password;
        return packet.str();
    }


    //// unregister_player
    UNREGISTER_PLAYER::UNREGISTER_PLAYER(std::string packet) : PACKET() {
        std::stringstream p_stream(packet);
        std::string line;

        // packetId will -always- be 3
        std::getline(p_stream, line, '\037');
        packetId = ntohs(static_cast<uint16_t>(std::stoul(line)));

        std::getline(p_stream, line, '\037');
        playerId = ntohs(static_cast<uint32_t>(std::stoul(line)));
    }

    UNREGISTER_PLAYER::UNREGISTER_PLAYER(Player *player) : PACKET(3) {
        playerId = player->playerId;
    }

    std::string UNREGISTER_PLAYER::UNREGISTER_PLAYER::pack() {
        std::stringstream packet("");
        packet << htons(packetId)
               << '\037' << htons(playerId);;
        return packet.str();
    }


    //// player_data
    REGISTER_PLAYER::REGISTER_PLAYER(std::string packet) : PACKET() {
        std::stringstream p_stream(packet);
        std::string line;

        // packetId will -always- be 4
        std::getline(p_stream, line, '\037');
        packetId = ntohs(static_cast<uint16_t>(std::stoul(line)));

        std::getline(p_stream, line, '\037');
        playerId = ntohs(static_cast<uint32_t>(std::stoul(line)));

        std::getline(p_stream, line, '\037');
        entityId = ntohs(static_cast<uint32_t>(std::stoul(line)));

        std::getline(p_stream, textureString, '\037');

        std::getline(p_stream, line, '\037');
        movementDirection = Direction(ntohs((uint32_t) std::stoul(line)));

        std::getline(p_stream, line, '\037');
        tilePositionX = ntohs(static_cast<uint32_t>(std::stoul(line)));

        std::getline(p_stream, line, '\037');
        tilePositionY = ntohs(static_cast<uint32_t>(std::stoul(line)));

        std::getline(p_stream, line, '\037');
        x = ntohs(static_cast<uint32_t>(std::stoul(line)));

        std::getline(p_stream, line, '\037');
        y = ntohs(static_cast<uint32_t>(std::stoul(line)));
    }

    REGISTER_PLAYER::REGISTER_PLAYER(Player *player) : PACKET(4) {
        playerId = player->playerId;
        entityId = player->entityId;
        textureString = player->textureString;
        movementDirection = player->movementDirection;
        tilePositionX = player->tilePositionX;
        tilePositionY = player->tilePositionY;
        x = player->x;
        y = player->y;
    }

    std::string REGISTER_PLAYER::REGISTER_PLAYER::pack() {
        std::stringstream packet("");
        packet << htons(packetId)
               << '\037' << htons(playerId)
               << '\037' << htons(entityId)
               << '\037' << textureString
               << '\037' << htons(movementDirection)
               << '\037' << htons(tilePositionX)
               << '\037' << htons(tilePositionY)
               << '\037' << htons(x)
               << '\037' << htons(y);
        return packet.str();
    }


}
