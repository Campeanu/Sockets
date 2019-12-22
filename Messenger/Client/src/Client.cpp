#include <Client/Client.h>

namespace Messenger {

    Client::Client(char* serverIp, int port)
        : serverIp{serverIp},
          port{port}
    {
        // Setup a socket and connection tools 
        this->host = gethostbyname(this->serverIp);

        bzero((char*)&this->sendSockAddr, sizeof(this->sendSockAddr)); 

        this->sendSockAddr.sin_family = AF_INET; 
        this->sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*this->host->h_addr_list));
        this->sendSockAddr.sin_port = htons(this->port);

        this->clientSd = socket(AF_INET, SOCK_STREAM, 0);
        
        // Try to connect ...
        this->status = connect(this->clientSd, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr));

        if(this->status < 0)
        {
            std::cout << "Error connecting to socket!" << std::endl; 
        }

        std::cout << "Connected to the server!" << std::endl;

        gettimeofday(&this->start1, NULL);

        while(true)
        {
            std::cout << ">";

            getline(std::cin, this->data);
            
            // Clear the buffer
            memset(&this->msg, 0, sizeof(this->msg));
            strcpy(this->msg, this->data.c_str());

            if(this->data == "exit")
            {
                send(this->clientSd, (char*)&this->msg, strlen(this->msg), 0);
                break;
            }

            this->bytesWritten += send(this->clientSd, (char*)&this->msg, strlen(this->msg), 0);

            std::cout << "Awaiting server response..." << std::endl;

            // Clear the buffer
            memset(&this->msg, 0, sizeof(this->msg)); 

            this->bytesRead += recv(this->clientSd, (char*)&this->msg, sizeof(this->msg), 0);

            if(!strcmp(this->msg, "exit"))
            {
                std::cout << "Server has quit the session" << std::endl;
                break;
            }

            std::cout << "Server: " << this->msg << std::endl;
        }

        gettimeofday(&this->end1, NULL);
        close(this->clientSd);

        std::cout << "********Session********" << std::endl;
        std::cout << "Bytes written: "   << this->bytesWritten << " Bytes read: " << this->bytesRead << std::endl;
        std::cout << "Elapsed time: "    << (this->end1.tv_sec - this->start1.tv_sec) << " secs" << std::endl;
        std::cout << "Connection closed" << std::endl;

    }

    Client::~Client()
    {

    }

} // namespace: Messenger