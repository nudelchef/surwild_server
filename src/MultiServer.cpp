#include "MultiServer.h"

#include <cstdio>          // puts
#include <cstdlib>
#include <cerrno>
#include <arpa/inet.h>      // close
#include <sys/types.h>      // send
#include <sys/socket.h>     // send

#include "SocketHandler.h"

MultiServer::MultiServer() = default;

MultiServer::~MultiServer() = default;

void MultiServer::start(const ushort port_, const ushort max_clients_) {

    port = port_;
    max_clients = max_clients_;
    bytesToRead = 0;

    client_socket = new int[max_clients_];
    users = new SocketHandler[max_clients_];



    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    //create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &allow_multiple_connections,
                   sizeof(allow_multiple_connections)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    isServerRunning = true;

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", port);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (isServerRunning) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for (i = 0; i < max_clients; i++) {
            //socket descriptor
            sockfd = client_socket[i];

            //if valid socket descriptor then add to read list
            if (sockfd > 0)
                FD_SET(sockfd, &readfds);

            //highest file descriptor number, need it for the select function
            if (sockfd > max_sd)
                max_sd = sockfd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n", new_socket,
                   inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;

                    SocketHandler sockhandl = SocketHandler(new_socket);
                    users[i] = sockhandl;

                    printf("Adding to list of sockets as %d ", i);
                    printf("with socketfd %d\n", new_socket);

                    //send all required info to the player
                    sockhandl.connect();


                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++) {
            sockfd = client_socket[i];
            SocketHandler *user = &users[i];

            if (FD_ISSET(sockfd, &readfds)) {
                if (!user->receive()) {
                    disconnectClient(i);
                }
            }
        }
    }
}

void MultiServer::broadcast(const std::string &message) {
    for (i = 0; i < max_clients; i++) {
        if (client_socket[i] == 0) {
            continue;
        }

        users[i].sendMessage(message);
    }
}

void MultiServer::disconnectClient(const ushort id) {
    //Somebody disconnected , get his details and print
    getpeername(sockfd, (struct sockaddr *) &address, \
        (socklen_t *) &addrlen);
    printf("Host disconnected , ip %s , port %d \n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    //Close the socket and mark as 0 in list for reuse
    users[i].disconnect();
    client_socket[i] = 0;

    //broadcast("someone has left.\n");
}
