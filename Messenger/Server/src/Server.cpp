#include <Server/Server.h>

namespace Messenger {

    Server::Server(int port)
        : port{port}
    {
        // Setup a socket and connection tools.
        // ------------------------------------
        bzero((char*)&this->servAddr, sizeof(this->servAddr));
        this->servAddr.sin_family = AF_INET;
        this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        this->servAddr.sin_port = htons(this->port);

        // Open stream oriented socket with internet address.
        // Also keep track of the socket descriptor.
        // -----------------------------------------
        this->serverSd = socket(AF_INET, SOCK_STREAM, 0);

        if(this->serverSd < 0)
        {
            std::cerr << "Error establishing the server socket" << std::endl;
            exit(0);
        }

        // Bind the socket to its local address.
        // -------------------------------------
        this->bindStatus = bind(this->serverSd, (struct sockaddr*) &this->servAddr, sizeof(this->servAddr));

        if(this->bindStatus < 0)
        {
            std::cerr << "Error binding socket to local address" << std::endl;
            exit(0);
        }

        std::cout << "Waiting for a client to connect..." << std::endl;

        // Listen for up to 5 requests at a time.
        // --------------------------------------
        listen(this->serverSd, 5);

        // Receive a request from client using accept.
        // We need a new address to connect with the client.
        // -------------------------------------------------
        this->newSockAddrSize = sizeof(this->newSockAddr);

        // Accept, create a new socket descriptor to handle the new connection with client.
        // -------------------------------------.
        this->newSd = accept(this->serverSd, (sockaddr *)&this->newSockAddr, &this->newSockAddrSize);

        if(this->newSd < 0)
        {
            std::cerr << "Error accepting request from client!" << std::endl;
            exit(1);
        }

        std::cout << "Connected with client!" << std::endl;

        // Lets keep track of the session time.
        // ------------------------------------
        gettimeofday(&this->start1, NULL);

        while(true)
        {
            // Receive a message from the client (listen).
            std::cout << "Awaiting client response..." << std::endl;

            // Clear the buffer.
            memset(&this->msg, 0, sizeof(this->msg)); 
            this->bytesRead += recv(this->newSd, (char*)&this->msg, sizeof(this->msg), 0);

            if(!strcmp(this->msg, "exit"))
            {
                std::cout << "Client has quit the session." << std::endl;
                break;
            }

            std::cout << "Client: " << this->msg << std::endl;
            std::cout << ">";

            getline(std::cin, this->data);

            // Clear the buffer
            memset(&this->msg, 0, sizeof(this->msg)); 

            strcpy(this->msg, this->data.c_str());

            if(this->data == "exit")
            {
                // Send to the client that server has closed the connection.
                send(this->newSd, (char*)&this->msg, strlen(this->msg), 0);
                break;
            }

            // Send the message to client.
            this->bytesWritten += send(this->newSd, (char*)&this->msg, strlen(this->msg), 0);
        }

        // We need to close the socket descriptors after we're all done.
        gettimeofday(&this->end1, NULL);
        close(this->newSd);
        close(this->serverSd);

        std::cout << "********Session********" << std::endl;
        std::cout << "Bytes written: "         << bytesWritten << " Bytes read: " << bytesRead << std::endl;
        std::cout << "Elapsed time: "          << (end1.tv_sec - start1.tv_sec) << " secs" << std::endl;
        std::cout << "Connection closed..."    << std::endl;
    }       
    
    Server::~Server()
    {

    }

} // namespace: Messenger