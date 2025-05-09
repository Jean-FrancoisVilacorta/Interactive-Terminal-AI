/*
** EPITECH PROJECT, 2025
** lib
** File description:
** is_str_float
*/


#include "my.h"

int is_float(char *str)
{
    int post_coma = 0;

    for (int i = 0; str[i]; i++){
        if (str[i] == '.' && !post_coma){
            post_coma = 1;
            continue;
        }
        if (is_nbr(str[i]) == FAIL)
            return FAIL;
    }
    return SUCCESS;
}
