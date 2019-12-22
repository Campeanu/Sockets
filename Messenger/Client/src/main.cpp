#include <Client/Client.h>

int main()
{
    Messenger::Client* client = new Messenger::Client("127.0.0.1", 20001);
    delete client;
}