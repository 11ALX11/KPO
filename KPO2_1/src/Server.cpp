#include "Server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int server_sockfd, client_sockfd;
int server_len; unsigned int client_len;
struct sockaddr_un server_address;
struct sockaddr_un client_address;

int server_start() {

//2. Удалите все старые сокеты и создайте неименованный сокет для сервера:

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

//3. Присвойте имя сокету:

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

//4. Создайте очередь запросов на соединение и ждите запроса клиента:

    handle();

    return 0;
}

void handle() {

    listen(server_sockfd, 5);
    while(1) {
        char ch;
        printf("server waiting\n");

//5. Примите запрос на соединение:

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

//6. Читайте и записывайте данные клиента с помощью client_sockfd:

        read(client_sockfd, &ch, 1);
        ch++;
        //parse
        //and answer
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}
