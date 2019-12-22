#include "Client/Client.h"

int main(int argc, char *argv[])
{
    Thor::Client* client = new Thor::Client("i7-workspace", 20001);
    delete client;
}