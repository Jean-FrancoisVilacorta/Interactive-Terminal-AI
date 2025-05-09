/*
** EPITECH PROJECT, 2024
** strstr
** File description:
** find a sub str in a str
*/
#include "my.h"

static int verify(char *str, char const *to_find)
{
    int i = 0;

    while (str[i] == to_find[i]){
        if (i == my_strlen(to_find) - 1){
            return 1;
        }
        i++;
    }
    return 0;
}

char *my_strstr(char *str, char const *to_find)
{
    if (my_strlen(str) == 0){
        return '\0';
    }
    if (my_strlen(str) < my_strlen(to_find)){
        return '\0';
    }
    if (str[0] == to_find[0]){
        if (verify(str, to_find)){
                return str;
            }
    }
    ++str;
    return my_strstr(str, to_find);
}
