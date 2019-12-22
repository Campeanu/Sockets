#include "Client/Client.h"

namespace Thor {

    void Client::error(const char *msg)
    {
        perror(msg);
        exit(1);
    }

    Client::Client(char* hostname, int portno)
        : hostname{hostname}, portno{portno}
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
        if (sockfd < 0) 
            error("ERROR opening socket");
        
        server = gethostbyname(hostname);
        
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        
        serv_addr.sin_family = AF_INET;
        
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        
        serv_addr.sin_port = htons(portno);
        
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
            error("ERROR connecting");
        
        printf("Please enter the message: ");
        
        bzero(buffer,256);
        
        fgets(buffer,255,stdin);
        
        n = write(sockfd, buffer, strlen(buffer));
        
        if (n < 0) 
            error("ERROR writing to socket");
        
        bzero(buffer,256);
        
        n = read(sockfd, buffer, 255);
        
        if (n < 0) 
            error("ERROR reading from socket");
        
        printf("%s\n", buffer);
        
        close(sockfd);
    }

    Client::~Client()
    {

    }

} // namespace: Thor