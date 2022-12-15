#include "CustomDB.h"

/*
    id      name    code
*/

#include <string.h>

void work_on_request(char* str) {
    if (strstr(str, "SELECT")-str == 0) {
        bool s_flag = false; // *_flag
        bool id_flag = false;
        bool name_flag = false;
        bool code_flag = false;
        
        char pars_str[1024]; strcpy(pars_str, str);
        //...

        if (strstr(str, "*") ) {

        }
    }
    else if (strstr(str, "INSERT")-str == 0) {

    }
    else if (strstr(str, "DELETE")-str == 0) {

    }
    else if (strstr(str, "UPDATE")-str == 0) {

    }
    else {
        strcpy(str, "Unknown command.\n");
    }
}
