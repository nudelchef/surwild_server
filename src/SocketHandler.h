#ifndef SOCKETHANDLER_H_INCLUDED
#define SOCKETHANDLER_H_INCLUDED

#include <vector>
#include <cstdint>
#include <string>

#include "PacketManager.h"

class Player;

class SocketHandler
{
public:

    SocketHandler();
    SocketHandler(int sockfd);
    ~SocketHandler();

    bool sendMessage(const std::string& message);
    int disconnect();

    void connect();

    bool receive();
    void receivedMessage(const std::string& message);

protected:
private:
    int sockfd;

    unsigned long bytesTotal;
    unsigned long bytesToRead;
    unsigned long bytesRead;
    unsigned long bytesRemaining;
    unsigned long bytesSent;
    unsigned long bytesToSend;
    unsigned long lengthValue;
    static const size_t CHUNK_LENGTH = 1024;
    char buffer[CHUNK_LENGTH];

    std::string full_message;

    Player* player;
};

#endif // SOCKETHANDLER_H_INCLUDED
