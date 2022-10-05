#include <iostream>
#include "Client.h"
#include "Server.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 1) {
        //server
        cout << "server\n";
        (new Server())->start();
    }
    else {
        //client
        cout << "client\n";
        (new Client())->start();
    }

    return 0;
}
