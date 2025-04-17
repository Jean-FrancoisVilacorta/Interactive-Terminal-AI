/*
** EPITECH PROJECT, 2025
** lib
** File description:
** strdup
*/

#include "my.h"
#include <stdlib.h>

char *my_strdup(char *str)
{
    char *new = malloc(sizeof(char) * my_strlen(str) + 1);

    return my_strcpy(new, str);
}
