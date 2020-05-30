#ifndef SOCKETHANDLER_H_INCLUDED
#define SOCKETHANDLER_H_INCLUDED

class SocketHandler
{
public:

    SocketHandler();
    SocketHandler(int sockfd);
    ~SocketHandler();

    virtual void receivedMessage(char* message);

    bool sendMessage(char *message);
    int disconnect();

protected:
private:
    int sockfd;
};

#endif // SOCKETHANDLER_H_INCLUDED
