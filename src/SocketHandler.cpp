#include "SocketHandler.h"

#include <string.h>         // strlen

#include <sys/types.h>      // send
#include <sys/socket.h>     // send
#include <unistd.h>         // close
#include <arpa/inet.h>      // close

#include <stdio.h>          // puts
SocketHandler::SocketHandler()
{
    sockfd = 0;
}

SocketHandler::SocketHandler(int sockfd_)
{
    sockfd = sockfd_;
}

SocketHandler::~SocketHandler()
{
}

void SocketHandler::receivedMessage(char* message)
{
    message[1024] = '\0';
    sendMessage(message);
}

bool SocketHandler::sendMessage(char* message)
{
    puts(message);
    return send(sockfd, message, strlen(message), 0) == strlen(message);
}

int SocketHandler::disconnect()
{
    return close( sockfd );
}
