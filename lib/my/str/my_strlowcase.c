/*
** EPITECH PROJECT, 2024
** my_strlowcase
** File description:
** set lowercase
*/
#include <stdio.h>
#include "my.h"
#include <stdlib.h>

char *my_strlowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 'Z' && str[i] >= 'A'){
            str[i] += 32;
        }
        i++;
    }
    return str;
}
