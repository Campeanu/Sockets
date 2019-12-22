#include <Server/Server.h>

int main()
{
    Messenger::Server* server = new Messenger::Server(20001);
    delete server;
}