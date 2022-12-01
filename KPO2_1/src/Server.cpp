#include "Server.h"
#include "CustomDB.h"

#include <iostream>
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

    setup_server_socket();
    handle();

    return 0;
}

void setup_server_socket() {
//2. Удалите все старые сокеты и создайте неименованный сокет для сервера:

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

//3. Присвойте имя сокету:

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
}

void handle() {

//4. Создайте очередь запросов на соединение и ждите запроса клиента:

    listen(server_sockfd, 5);
    while(1) {
        printf("server waiting\n");

//5. Примите запрос на соединение:

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

//6. Читайте и записывайте данные клиента с помощью client_sockfd:

        get_requests();

        close(client_sockfd);
    }
}

void get_requests() {
    char ch = '1';
    char str[1024];

    int n = 0;
    while(ch != '\0' && ch != '\n') {
        read(client_sockfd, &ch, 1);
        str[n++] = ch;
    }

    //parse

    //CustomDB.h
    //response = work_on_request(char *str);

        //and answer
    char response[255] = "Hello client!\n";
    write(client_sockfd, response, 255);
}
