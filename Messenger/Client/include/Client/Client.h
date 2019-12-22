#ifndef CLIENT_H
#define CLIENT_H

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

    class Client {
    public:
        Client(char* serverIp, int port);
        virtual ~Client();
    private:
        // Grab the IP address and port number.
        // ------------------------------------ 
        char* serverIp; 
        int port; 

        // Create a message buffer.
        // ------------------------
        char msg[1500]; 

        // Setup a socket and connection tools.
        // ------------------------------------
        struct hostent* host; 
        sockaddr_in sendSockAddr;

        int clientSd;

        // Try to connect ...
        int status;

        int bytesRead, bytesWritten = 0;

        struct timeval start1, end1;

        std::string data;

    }; // class: Client

} // namespace: Messenger

#endif // CLIENT_H