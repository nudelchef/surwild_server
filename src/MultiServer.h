#ifndef MULTISERVER_H_INCLUDED
#define MULTISERVER_H_INCLUDED

#include <netinet/in.h>     // sockaddr_in
#include <string>

#include "PacketManager.h"

class SocketHandler;

class MultiServer {
public:

    MultiServer();

    ~MultiServer();

    void start(ushort port, ushort max_clients);

    void broadcast(const std::string &message);

    void disconnectClient(ushort id);

    static MultiServer &instance() {
        static MultiServer server;
        return server;
    };

protected:
private:

    SocketHandler *users{};
    ushort bytesToRead{};

    ushort port{};
    ushort max_clients{};

    bool isServerRunning{};

    int allow_multiple_connections = 1;

    int master_socket{};
    int addrlen{};
    int new_socket{};
    int *client_socket{};
    int activity{};
    int valread{};
    int sockfd{};

    int max_sd{};
    struct sockaddr_in address{};

    ushort i{};

    char buffer[1024]{}; //data buffer of 1K

    //set of socket descriptors
    fd_set readfds{};
};

#endif // MULTISERVER_H_INCLUDED
