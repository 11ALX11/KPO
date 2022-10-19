#include "Client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int sockfd;

int client_start() {

    setup_socket();

    send_requests();

    close(sockfd);

    return 0;
}

void setup_socket() {

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
        perror("oops : client1");
        exit(1);
    }
}

void send_requests() {
    char ch = 'A';

//5. Теперь вы можете читать и писать через sockfd:

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
}
