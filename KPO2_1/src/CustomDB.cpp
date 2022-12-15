#include "CustomDB.h"

/*  table
    id      name    code
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void work_on_request(char* str) {
    printf("%s\n", str);
    int nresp = 0;

    if (strstr(str, "SELECT")-str == 0) {
        bool s_flag = false; // *_flag
        bool id_flag = false;
        bool name_flag = false;
        bool code_flag = false;
        bool where_flag = false;
        int where_pos = 3000;

        if (strstr(str, "WHERE")-str > 0 && strstr(str, "WHERE")-str < where_pos) {
            where_flag = true;
            where_pos = strstr(str, "WHERE")-str;
        }

        if (strstr(str, "*")-str > 0 && strstr(str, "*")-str < where_pos) {
            s_flag = true;
        }
        if (strstr(str, "id")-str > 0 && strstr(str, "id")-str < where_pos) {
            id_flag = true;
        }
        if (strstr(str, "name")-str > 0 && strstr(str, "name")-str < where_pos) {
            name_flag = true;
        }
        if (strstr(str, "code")-str > 0 && strstr(str, "code")-str < where_pos) {
            code_flag = true;
        }

        //...

        if (!s_flag && !id_flag && !name_flag && !code_flag) {
            strcpy(str, "Invalid SELECT.\n\0");
            return;
        }

        int fd; char chr;
        if ((fd = open("db.txt", O_CREAT | O_RDWR, 0666)) < 0) {
            perror("Error opening db!");
            exit(-1);
        }

        int col = 0;
        while (read(fd, &chr, 1)) {
            if (chr == ' ') {
                col++;
                str[nresp++] = '\t';
                continue;
            }
            if (chr == '\n') {
                col = 0;
                str[nresp++] = '\n';
                continue;
            }

            if (col == 0 && (id_flag || s_flag)) {
                str[nresp++] = chr;
            }
            if (col == 1 && (name_flag || s_flag)) {
                str[nresp++] = chr;
            }
            if (col == 2 && (code_flag || s_flag)) {
                str[nresp++] = chr;
            }
        }

        close(fd);
    }
    else if (strstr(str, "INSERT")-str == 0) {

    }
    else if (strstr(str, "DELETE")-str == 0) {

    }
    else if (strstr(str, "UPDATE")-str == 0) {

    }
    else {
        strcpy(str, "Unknown command.\n\0");
        return;
    }

    str[nresp++] = '\0';
}
