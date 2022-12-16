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
    int nresp = 0;

    if (strstr(str, "SELECT")-str == 0) {
        bool s_flag = false; // *_flag
        bool id_flag = false;
        bool name_flag = false;
        bool code_flag = false;
        bool where_flag = false;
        int where_pos = 3000;

        int nbuf = 0;
        char buf[1024];

        if (strstr(str, "WHERE")-str > 0 && strstr(str, "WHERE")-str < where_pos) {
            where_flag = true;
            where_pos = strstr(str, "WHERE")-str;
        }

        //Columns
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
            strcpy(str, "Invalid SELECT: no columns.\n\0");
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
                buf[nbuf++] = '\t';
                continue;
            }
            if (chr == '\n') {
                col = 0;
                buf[nbuf++] = '\n';
                continue;
            }

            if (col == 0 && (id_flag || s_flag)) {
                buf[nbuf++] = chr;
            }
            if (col == 1 && (name_flag || s_flag)) {
                buf[nbuf++] = chr;
            }
            if (col == 2 && (code_flag || s_flag)) {
                buf[nbuf++] = chr;
            }
        }

        close(fd);
        buf[nbuf++] = '\0';

        //WHERE
        if (strstr(str, "id")-str > where_pos && strstr(str, "id")-str < strlen(str)) {
            if (!(id_flag || s_flag)) {
                strcpy(str, "Wrong WHERE: column isnt selected.\n\0");
                return;
            }
        }
        if (strstr(str, "name")-str > where_pos && strstr(str, "name")-str < strlen(str)) {
            if (!(name_flag || s_flag)) {
                strcpy(str, "Wrong WHERE: column isnt selected.\n\0");
                return;
            }
        }
        if (strstr(str, "code")-str > where_pos && strstr(str, "code")-str < strlen(str)) {
            if (!(code_flag || s_flag)) {
                strcpy(str, "Wrong WHERE: column isnt selected.\n\0");
                return;
            }
        }

        if (where_flag) {
            id_flag = false;
            name_flag = false;
            code_flag = false;

            bool eq = false;    // =
            bool mr = false;    // >
            bool ls = false;    // <

            int l = where_pos+5;
            char word[64]; int nword = 0;
            do {
                l++;
                if (str[l] == ' ' || str[l] == '\t' || str[l] == '\n' || str[l] == '\0') {
                    word[nword++] = '\0';

                    if ((id_flag || name_flag || code_flag) && (eq || mr || ls)) {
                        char buf2[1024]; int nbuf2 = 0;
                        char word2[64]; int nword2 = 0;

                        bool true_clause = false;

                        int i = 0; int j = 0; int col = 0;
                        while (buf[i] != '\0') {
                            if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n') {
                                if (nword2 > 0) {
                                    word2[nword2++] = '\0';
                                    
                                    if (eq) {
                                        if (strcmp(word, word2) == 0) {
                                            true_clause = true;
                                        }
                                    }
                                    else if (mr) {
                                        if (strcmp(word, word2) < 0) {
                                            true_clause = true;
                                        }
                                    }
                                    else if (ls) {
                                        if (strcmp(word, word2) > 0) {
                                            true_clause = true;
                                        }
                                    }

                                    nword2 = 0;
                                }

                                col++;
                            }
                            if (buf[i] == '\n') {
                                if (true_clause) {
                                    for (int k = j; k <= i; k++) {
                                        buf2[nbuf2++] = buf[k];
                                    }
                                }

                                j = i+1;
                                col = 0;
                                true_clause = false;
                            }

                            if (!(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')) {
                                if (col == 0 && (id_flag)) {
                                    word2[nword2++] = buf[i];
                                }
                                if (col == 1 && (name_flag)) {
                                    word2[nword2++] = buf[i];
                                }
                                if (col == 2 && (code_flag)) {
                                    word2[nword2++] = buf[i];
                                }
                            }

                            i++;
                        }
                        buf2[nbuf2++] = '\0';

                        id_flag = false;
                        name_flag = false;
                        code_flag = false;

                        eq = false;
                        mr = false;
                        ls = false;

                        strcpy(buf, buf2);
                    }

                    if (strcmp(word, "id") == 0) {
                        id_flag = true;
                    }
                    if (strcmp(word, "name") == 0) {
                        name_flag = true;
                    }
                    if (strcmp(word, "code") == 0) {
                        code_flag = true;
                    }

                    if (strcmp(word, "=") == 0) {
                        eq = true;
                    }
                    if (strcmp(word, ">") == 0) {
                        mr = true;
                    }
                    if (strcmp(word, "<") == 0) {
                        ls = true;
                    }

                    nword = 0;
                    continue;
                }

                word[nword++] = str[l];

            } while (str[l] != '\n' && str[l] != '\0');
        }

        strcpy(str, buf);
        return;
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
