/*
** EPITECH PROJECT, 2025
** lib
** File description:
** dprint
*/

#include <unistd.h>
#include "my.h"


int find_flag(int fd, char flag, va_list arg)
{
    for (int i = 0; dprint_function[i].function; i++){
        if (flag == dprint_function[i].flag){
            dprint_function[i].function(fd, arg);
            return SUCCESS;
        }
    }
    return FAIL;
}

int my_dprintf(int fd, char *str, ...)
{
    va_list arg;

    va_start(arg, str);
    for (int i = 0; str[i]; i++){
        if (str[i] == '%'){
            find_flag(fd, str[i + 1], arg);
            i += 2;
        }
        if (!str[i])
            break;
        write(fd, &str[i], 1);
    }
    va_end(arg);
    return SUCCESS;
}
