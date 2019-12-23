#include <Server/Server.h>

namespace Messenger {

    Server::Server(int port)
        : port{port}
    {
        // Setup a socket and connection tools.
        // ------------------------------------
        
        // sockaddr_in servAddr
        /* Set N bytes of S to 0.  */
        bzero((char*)&this->servAddr, sizeof(this->servAddr));
        
        /* AF_INET ---> Address families.  */
        /*
            AF_INET is an address family that is used to designate the type of addresses that your 
            socket can communicate with (in this case, Internet Protocol v4 addresses). When you create a
            socket, you have to specify its address family, and then you can only use addresses of that type 
            with the socket.
        */
        this->servAddr.sin_family = AF_INET;

        /* htonl()
        Functions to convert between host and network byte order.

        Please note that these functions normally take `unsigned long int' or
        `unsigned short int' values as arguments and also return them.  But
        this was a short-sighted decision since on different systems the types
        may have different representations but the values are always the same.  
        */

        /* sin_addr -> Internet address.  */
        /* INADDR_ANY -> Address to accept any incoming messages.  */
        this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        
        // sin_port -> /* Port number. */ 
        this->servAddr.sin_port = htons(this->port);

        // Open stream oriented socket with internet address.
        // Also keep track of the socket descriptor.
        // -----------------------------------------

        /* socket()
        Create a new socket of type TYPE in domain DOMAIN, using
        protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
        Returns a file descriptor for the new socket, or -1 for errors.  
        */
        this->serverSd = socket(AF_INET, SOCK_STREAM, 0);

        if(this->serverSd < 0)
        {
            std::cerr << "Error establishing the server socket" << std::endl;
            exit(0);
        }

        // Bind the socket to its local address.
        // -------------------------------------
        /* Give the socket FD the local address ADDR (which is LEN bytes long).  */
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

        /* accept()
        Await a connection on socket FD.
        When a connection arrives, open a new socket to communicate with it,
        set *ADDR (which is *ADDR_LEN bytes long) to the address of the connecting
        peer and *ADDR_LEN to the address's actual length, and return the
        new socket's descriptor, or -1 for errors.

        This function is a cancellation point and therefore not marked with __THROW.  
        */

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
            // -----------------
            /* Set N bytes of S to C. */
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

            // Clear the buffer.
            // -----------------
            /* Set N bytes of S to C. */
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