#ifndef MULTISERVER_H_INCLUDED
#define MULTISERVER_H_INCLUDED

#include <netinet/in.h>     // sockaddr_in

class SocketHandler;

class MultiServer
{
public:

    MultiServer(short port, short max_clients);
    ~MultiServer();

    void start();

    void broadcast(char* message);

    void disconnectClient(short id);

protected:
private:

    SocketHandler* users;

    short port;
    short max_clients;

    bool isServerRunning;

    int allow_multiple_connections = 1;

    int master_socket;
    int addrlen;
    int new_socket;
    int* client_socket;
    int activity;
    short i;
    int valread;
    int sockfd;

    int max_sd;
    struct sockaddr_in address;

    char buffer[1024]; //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;
};

#endif // MULTISERVER_H_INCLUDED
