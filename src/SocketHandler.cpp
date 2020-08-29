#include "SocketHandler.h"

#include <iostream>
#include <string.h>         // strlen

#include <sys/types.h>      // send
#include <sys/socket.h>     // send
#include <unistd.h>         // close
#include <arpa/inet.h>      // close

#include <stdio.h>          // puts
SocketHandler::SocketHandler()
{
    sockfd = 0;
    bytesToRead = 0ul;
}

SocketHandler::SocketHandler(int sockfd_)
{
    sockfd = sockfd_;
    std::cout << "[" << sockfd << "] received." << std::endl;
    bytesToRead = 0ul;
}

SocketHandler::~SocketHandler()
{
}

void SocketHandler::receivedMessage(char* message)
{
    std::cout << "[" << message << "] received. ";

    /*
    unsigned int lastMatch = 0;
    for(unsigned int i = 0; i < 1024; i++) {

        //std::cout << message[i];

        if (message[i] == '\0')
        {
            while (!message_chunks.empty())
            {
                //std::cout << message_chunks.back();
                message_chunks.pop_back();
            }

            for (unsigned int b = lastMatch; b <= i; b++)
            {
                std::cout << message[b];
            }
            std::cout << std::endl;

            lastMatch = i;
        }
    }
    unsigned long additional_length = 1024 - lastMatch - 1;
    std::cout << "additional_length:" << additional_length << std::endl;

    if (additional_length != 0)
    {
        char buffer[additional_length];
        memcpy(&buffer[0], &message[0] + lastMatch, additional_length);
        std::cout << "add:" << buffer << std::endl;
        message_chunks.push_back(buffer);
    }

    std::cout << "STILL IN BUFFER:" << std::endl;

    while (!message_chunks.empty())
    {
        std::cout << message_chunks.back();
        message_chunks.pop_back();
    }
    std::cout << std::endl;
    */



    //sendMessage(message);

    //bytesToRead -= std::min(1024ul, bytesToRead);
    bytesToRead -= strlen(message);
    std::cout << "(" << strlen(message) << "bytes) - " << bytesToRead << " bytes left." << std::endl;
}

bool SocketHandler::sendMessage(char* message)
{
    puts(message);
    std::cout << "sending on sockfd: " << sockfd << std::endl;
    return send(sockfd, message, strlen(message), 0) == strlen(message);
}

int SocketHandler::disconnect()
{
    return close( sockfd );
}
