/*
** EPITECH PROJECT, 2024
** my_is_nbr
** File description:
** is char nbr
*/

#include "my.h"

int is_nbr(char c)
{
    if (c <= 57 && c >= 48){
        return (int) c - 48;
    }
    return FAIL;
}

int is_str_int(char *str)
{
    int i = 0;

    if (str[i] == '-')
        i++;
    while (str[i]){
        if (is_nbr(str[i]) == FAIL)
            return FAIL;
        i++;
    }
    return SUCCESS;
}
