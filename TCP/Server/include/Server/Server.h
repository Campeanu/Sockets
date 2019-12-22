#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

namespace Thor {
    
    class Server
    {
    public:
        Server(int portno);
        virtual ~Server();
    private:
        void error(const char *msg);
    private:
        int sockfd, newsockfd, portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
    };

} // namespace: Thor

#endif // SERVER_H