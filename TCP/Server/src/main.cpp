#include "Server/Server.h"

int main(int argc, char *argv[])
{
    Thor::Server* server = new Thor::Server(20001);
    delete server;
}