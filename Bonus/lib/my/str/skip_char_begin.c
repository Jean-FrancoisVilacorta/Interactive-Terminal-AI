/*
** EPITECH PROJECT, 2025
** skip char begin
** File description:
** skip char of beginning
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"

char *skip_char_begin(char *str, int nb)
{
    int i = 0;
    int len = (my_strlen(str) - nb);
    char *str_skip = malloc(sizeof(char) * (len + 1));

    if (str_skip == NULL)
        return NULL;
    for (; str[nb] != '\0'; nb++) {
        str_skip[i] = str[nb];
        i++;
    }
    str_skip[i] = '\0';
    return str_skip;
}
