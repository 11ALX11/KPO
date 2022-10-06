#include "Client.h"
#include "Server.h"

//Основы программирования в Linux [Нейл Мэтью]

int main(int argc, char *argv[])
{
    if (argc > 1) {
        //server
        return server_start();
    }
    else {
        //client
        return client_start();
    }

    //return 0;
}
