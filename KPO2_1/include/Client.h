#ifndef CLIENT_H
#define CLIENT_H

int client_start();
void setup_client_socket();
void send_requests(char *send_str, int nbytes);
//return nbytes
int ask_string(char *str);

#endif // CLIENT_H
