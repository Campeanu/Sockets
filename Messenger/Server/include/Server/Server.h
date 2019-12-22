#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>

#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <netdb.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/uio.h>

namespace Messenger {

    class Server {
    public:
        Server(int port);
        virtual ~Server();
    private:

    // Grab the port number.
    // ---------------------
    int port;

    // Buffer to send and receive messages with.
    // -----------------------------------------
    char msg[1500];

    // Setup a socket and connection tools.
    // ------------------------------------
    sockaddr_in servAddr;

    // Open stream oriented socket with internet address.
    // Also keep track of the socket descriptor.
    // -----------------------------------------    
    int serverSd;

    // Bind the socket to its local address.
    // -------------------------------------
    int bindStatus;


    // Receive a request from client using accept.
    // We need a new address to connect with the client.
    // -------------------------------------------------
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize;

    // Accept, create a new socket descriptor to andle the new connection with client.
    // -------------------------------------------------------------------------------
    int newSd;

    // Lets keep track of the session time.
    // ------------------------------------
    struct timeval start1, end1;

    // Also keep track of the amount of data sent as well.
    // ---------------------------------------------------
    int bytesRead, bytesWritten = 0;

    // While loop !
    std::string data;

    }; // class: Server

} // namespace: Messenger

#endif // SERVER_H