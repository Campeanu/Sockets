#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define __USE_MISC
#include <netdb.h>

namespace Thor {

    class Client {
    public:
        Client(char* hostname, int portno);
        virtual ~Client();
    private:
        void error(const char *msg);
    private:
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        char buffer[256];
        char* hostname;
        int port;
    };

} // THor

#endif // CLIENT_H