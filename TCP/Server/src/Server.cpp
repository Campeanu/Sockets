#include "Server/Server.h"

namespace Thor {

    void Server::error(const char *msg)
    {
        perror(msg);
        exit(1);
    }

    Server::Server(int portno)
        : portno {portno}
    {
        // create a socket
        // socket(int domain, int type, int protocol)
        sockfd =  socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
        error("ERROR opening socket");

        // clear address structure
        bzero((char *) &serv_addr, sizeof(serv_addr));

        /* setup the host_addr structure for use in bind call */
        // server byte order
        serv_addr.sin_family = AF_INET;  

        // automatically be filled with current host's IP address
        serv_addr.sin_addr.s_addr = INADDR_ANY;  

        // convert short integer value for port must be converted into network byte order
        serv_addr.sin_port = htons(portno);

        // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
        // bind() passes file descriptor, the address structure, 
        // and the length of the address structure
        // This bind() call will bind  the socket to the current IP address on port, portno
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) 
                error("ERROR on binding");

        // This listen() call tells the socket to listen to the incoming connections.
        // The listen() function places all incoming connection into a backlog queue
        // until accept() call accepts the connection.
        // Here, we set the maximum size for the backlog queue to 5.
        listen(sockfd, 5);

        // The accept() call actually accepts an incoming connection
        clilen = sizeof(cli_addr);

        // This accept() function will write the connecting client's address info 
        // into the the address structure and the size of that structure is clilen.
        // The accept() returns a new socket file descriptor for the accepted connection.
        // So, the original socket file descriptor can continue to be used 
        // for accepting new connections while the new socker file descriptor is used for
        // communicating with the connected client.
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        
        if (newsockfd < 0) 
            error("ERROR on accept");

        printf("server: got connection from %d port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

        // This send() function sends the 13 bytes of the string to the new socket
        send(newsockfd, "Hello, world!\n", 13, 0);

        bzero(buffer,256);

        n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        
        printf("Here is the message: %s\n",buffer);

        close(newsockfd);
        close(sockfd);
    }

    Server::~Server()
    {

    }

}