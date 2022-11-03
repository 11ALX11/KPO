#include "Client.h"

#include <iostream>

#include <cstdio>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int sockfd;

int client_start() {

    setup_client_socket();

    char str[1024];
    int nbytes = ask_string(str);
    if (nbytes <= 1) {
        send_requests("Hello server!\n", 14);
    }
    else {
        send_requests(str, nbytes);
    }

    close(sockfd);

    return 0;
}

int ask_string(char *str) {
    printf("Enter request (up to 1024 characters):\n");
    fgets(str, sizeof(str), stdin);

    int i = 0;
    while (str[i] != '\n' && str[i] != '\0') i++;
    return ++i;
}

void setup_client_socket() {

    int len;
    struct sockaddr_un address;
    int result;

//2. Создайте сокет для клиента:

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

//3. Назовите сокет по согласованию с сервером:

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

//4. Соедините ваш сокет с сокетом сервера:

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("Error while connecting to server");
        exit(1);
    }
}

void send_requests(char *send_str, int nbytes) {
    char ch;

//5. Теперь вы можете читать и писать через sockfd:

    write(sockfd, send_str, nbytes);
    while (read(sockfd, &ch, 1)) {
        printf("%c", ch);
    }
}
