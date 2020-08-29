#ifndef SOCKETHANDLER_H_INCLUDED
#define SOCKETHANDLER_H_INCLUDED

#include <vector>
#include <cstdint>

class SocketHandler
{
public:

    SocketHandler();
    SocketHandler(int sockfd);
    ~SocketHandler();

    virtual void receivedMessage(char* message);

    bool sendMessage(char *message);
    int disconnect();

    uint64_t bytesToRead;

protected:
private:
    int sockfd;

    std::vector<char*> message_chunks;
};

#endif // SOCKETHANDLER_H_INCLUDED
