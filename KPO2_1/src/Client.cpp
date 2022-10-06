#include "Client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int client_start() {

    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

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

//5. Теперь вы можете читать и писать через sockfd:

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);

    close(sockfd);

    exit(0);

    return 0;
}
