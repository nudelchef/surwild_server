#include "SocketHandler.h"

#include <iostream>
#include <string.h>         // strlen

#include <sys/types.h>      // send
#include <sys/socket.h>     // send
#include <unistd.h>         // close
#include <arpa/inet.h>      // close
#include <string>

#include <stdio.h>          // puts

#include "Player.h"
#include "MultiServer.h"
#include "PacketManager.h"

SocketHandler::SocketHandler() {
    sockfd = 0;
    player = nullptr;
}

SocketHandler::SocketHandler(int sockfd_) {
    sockfd = sockfd_;
    bytesTotal = 0ul;
    bytesToRead = 0ul;
    bytesRead = 0ul;
    bytesRemaining = 0ul;
    full_message = "";

    player = new Player(this);
}

SocketHandler::~SocketHandler() {
}

bool SocketHandler::receive() {
    if (bytesRemaining == 0) {
        if (recv(sockfd, buffer, sizeof(unsigned long), 0) != sizeof(unsigned long)) {
            return false;
        }
        memcpy(&bytesTotal, &buffer[0], sizeof(unsigned long));

        bytesTotal = ntohl((unsigned long) bytesTotal);
        bytesRemaining = bytesTotal;
        full_message = "";

        return true;
    } else {

        bytesToRead = std::min(CHUNK_LENGTH, bytesRemaining);

        bytesRead = recv(sockfd, &buffer, bytesToRead, 0);

        if (bytesRead < 0) return false;
        else bytesRemaining -= bytesRead;

        full_message.append(&buffer[0], bytesRead);

        if (bytesRemaining == 0) {
            std::cout << "received: [" << full_message << "] length: " << full_message.length() << std::endl;

            receivedMessage(full_message);
        }

        return true;
    }
}

void SocketHandler::receivedMessage(const std::string &message) {
    sendMessage(message);
}

bool SocketHandler::sendMessage(const std::string &message) {
    bytesTotal = message.length();
    bytesRemaining = bytesTotal;
    bytesSent = 0;
    bytesToSend = 0;

    std::cout << "sending on sockfd: (" << sockfd << ") [" << message << "] (" << bytesTotal << ") bytes." << std::endl;


    lengthValue = htonl((unsigned long) bytesTotal);
    if (send(sockfd, (const char *) &lengthValue, sizeof(lengthValue), 0) < 0) {
        return false;
    }

    do {
        bytesToSend = std::min(CHUNK_LENGTH, bytesRemaining);

        bytesSent = send(sockfd, message.c_str() + (bytesTotal - bytesRemaining), bytesToSend, 0);

        if (bytesSent < 0) return false;
        else bytesRemaining -= bytesSent;

    } while (bytesRemaining > 0);

    return true;
}

void SocketHandler::connect() {
    std::string playerData = PACKET::REGISTER_PLAYER(player).pack();

    MultiServer::instance().broadcast(playerData);
}

int SocketHandler::disconnect() {
    if (player)
        free(player);
    return close(sockfd);
}
