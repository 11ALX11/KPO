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
    
    bool where_flag = false;
    int where_pos = 3000;
    if (strstr(str, "WHERE")-str > 0 && strstr(str, "WHERE")-str < where_pos) {
        where_flag = true;
        where_pos = strstr(str, "WHERE")-str;
    }


    //SELECT
    if (strstr(str, "SELECT")-str == 0) {
        bool s_flag = false; // *_flag
        bool id_flag = false;
        bool name_flag = false;
        bool code_flag = false;

        int nbuf = 0;
        char buf[1024];

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
            if (chr == ' ' || chr == '\t') {
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
        if (where_flag) {
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


    //INSERT
    else if (strstr(str, "INSERT")-str == 0) {
        int col = 0; int i = 6;
        char buf[1024]; int nbuf = 0;
        do {
            i++;
            if (str[i] == ' ' || str[i] == ',') {
                if (nbuf > 0 && buf[nbuf-1] != '\t') {
                    buf[nbuf++] = '\t';
                    col++;
                }
                continue;
            }

            buf[nbuf++] = str[i];

            if (col > 2) {
                strcpy(str, "Wrong amount of columns.\n\0");
                return;
            }
        } while (i < where_pos && str[i] != '\n' && str[i] != '\0');
        if (col < 2) {
            strcpy(str, "Wrong amount of columns.\n\0");
            return;
        }

        int fd;
        if ((fd = open("db.txt", O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0) {
            perror("Error opening db!");
            exit(-1);
        }

        write(fd, buf, nbuf);

        close(fd);
        
        strcpy(str, "Ok.\n\0");
    }


    //DELETE
    else if (strstr(str, "DELETE")-str == 0) {
        int nbuf = 0;
        char buf[1024];

        //WHERE
        if (where_flag) {
            // geting bufer
            int fd; char chr;
            if ((fd = open("db.txt", O_CREAT | O_RDWR, 0666)) < 0) {
                perror("Error opening db!");
                exit(-1);
            }

            int col = 0;
            while (read(fd, &chr, 1)) {
                if (chr == ' ' || chr == '\t') {
                    col++;
                    buf[nbuf++] = '\t';
                    continue;
                }
                if (chr == '\n') {
                    col = 0;
                    buf[nbuf++] = '\n';
                    continue;
                }

                buf[nbuf++] = chr;
            }

            close(fd);
            buf[nbuf++] = '\0';
            
            bool id_flag = false;
            bool name_flag = false;
            bool code_flag = false;

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
                                if (!true_clause) {
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

        int fd;
        if ((fd = open("db.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0) {
            perror("Error opening db!");
            exit(-1);
        }

        write(fd, buf, strlen(buf));

        close(fd);
        
        strcpy(str, "Ok.\n\0");
    }


    //UPDATE
    else if (strstr(str, "UPDATE")-str == 0) {
        bool id_sflag = false;
        bool name_sflag = false;
        bool code_sflag = false;

        int set_pos = strstr(str, "SET")-str;
        
        if ( !( (set_pos > 0) && (set_pos < strlen(str)) ) ) {
            strcpy(str, "Misding SET.\n\0");
            return;
        }


        int nid_word = 0;
        char id_word[64];
        if (strstr(str, "id")-str > set_pos && strstr(str, "id")-str < where_pos) {
            id_sflag = true;

            int i = strstr(str, "id")-str+2;
            while (1) {
                if (str[i] == ' ' || str[i] == '\t' || str[i] ==  '=') {
                    if (!(nid_word > 0)) {
                        i++;
                        continue;
                    }

                    break;
                }
                else {
                    id_word[nid_word++] = str[i++];
                }
            }
        }

        int nname_word = 0;
        char name_word[64];
        if (strstr(str, "name")-str > set_pos && strstr(str, "name")-str < where_pos) {
            name_sflag = true;

            int i = strstr(str, "name")-str+4;
            while (1) {
                if (str[i] == ' ' || str[i] == '\t' || str[i] ==  '=') {
                    if (!(nname_word > 0)) {
                        i++;
                        continue;
                    }

                    break;
                }
                else {
                    name_word[nname_word++] = str[i++];
                }
            }
        }

        int ncode_word = 0;
        char code_word[64];
        if (strstr(str, "code")-str > set_pos && strstr(str, "code")-str < where_pos) {
            code_sflag = true;

            int i = strstr(str, "code")-str+4;
            while (1) {
                if (str[i] == ' ' || str[i] == '\t' || str[i] ==  '=') {
                    if (!(ncode_word > 0)) {
                        i++;
                        continue;
                    }

                    break;
                }
                else {
                    code_word[ncode_word++] = str[i++];
                }
            }
        }

        if (!id_sflag && !name_sflag && !code_sflag) {
            strcpy(str, "Invalid SET: no columns.\n\0");
            return;
        }

        //WHERE
        if (where_flag) {
            int nbuf = 0;
            char buf[1024];

            // geting bufer
            int fd; char chr;
            if ((fd = open("db.txt", O_CREAT | O_RDWR, 0666)) < 0) {
                perror("Error opening db!");
                exit(-1);
            }

            int col = 0;
            while (read(fd, &chr, 1)) {
                if (chr == ' ' || chr == '\t') {
                    col++;
                    buf[nbuf++] = '\t';
                    continue;
                }
                if (chr == '\n') {
                    col = 0;
                    buf[nbuf++] = '\n';
                    continue;
                }

                buf[nbuf++] = chr;
            }

            close(fd);
            buf[nbuf++] = '\0';
            
            bool id_flag = false;
            bool name_flag = false;
            bool code_flag = false;

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
                        char id_word2[64]; int nid_word2 = 0;
                        char name_word2[64]; int nname_word2 = 0;
                        char code_word2[64]; int ncode_word2 = 0;

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
                                    if (id_sflag) {
                                        for (int k = 0; k < nid_word; k++) {
                                            buf2[nbuf2++] = id_word[k];
                                        }
                                    }
                                    else {
                                        for (int k = 0; k < nid_word2; k++) {
                                            buf2[nbuf2++] = id_word2[k];
                                        }
                                    }
                                    buf2[nbuf2++] = '\t';

                                    if (name_sflag) {
                                        for (int k = 0; k < nname_word; k++) {
                                            buf2[nbuf2++] = name_word[k];
                                        }
                                    }
                                    else {
                                        for (int k = 0; k < nname_word2; k++) {
                                            buf2[nbuf2++] = name_word2[k];
                                        }
                                    }
                                    buf2[nbuf2++] = '\t';

                                    if (code_sflag) {
                                        for (int k = 0; k < ncode_word; k++) {
                                            buf2[nbuf2++] = code_word[k];
                                        }
                                    }
                                    else {
                                        for (int k = 0; k < ncode_word2; k++) {
                                            buf2[nbuf2++] = code_word2[k];
                                        }
                                    }
                                    buf2[nbuf2++] = '\n';
                                }
                                else {
                                    for (int k = j; k <= i; k++) {
                                        buf2[nbuf2++] = buf[k];
                                    }
                                }

                                j = i+1;
                                col = 0;
                                nid_word2 = 0;
                                nname_word2 = 0;
                                ncode_word2 = 0;
                                true_clause = false;
                            }

                            if (!(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')) {
                                if (col == 0) {
                                    id_word2[nid_word2++] = buf[i];

                                    if (id_flag) {
                                        word2[nword2++] = buf[i];
                                    }
                                }
                                if (col == 1) {
                                    name_word2[nname_word2++] = buf[i];

                                    if (name_flag) {
                                        word2[nword2++] = buf[i];
                                    }
                                }
                                if (col == 2) {
                                    code_word2[ncode_word2++] = buf[i];

                                    if (code_flag) {
                                        word2[nword2++] = buf[i];
                                    }
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
        
            if ((fd = open("db.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0) {
                perror("Error opening db!");
                exit(-1);
            }

            write(fd, buf, strlen(buf));

            close(fd);
        }
        else {
            strcpy(str, "Missing WHERE clasue.\n\0");
            return;
        }

        strcpy(str, "Ok.\n\0");
    }


    else {
        strcpy(str, "Unknown command.\n\0");
    }
}
