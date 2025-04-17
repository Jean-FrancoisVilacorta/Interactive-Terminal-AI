/*
** EPITECH PROJECT, 2025
** lib my
** File description:
** clean str
*/

#include "my.h"
#include <stdlib.h>

char *clean_str(char *str, char c)
{
    char *clean = malloc(sizeof(char) * (len_without_char(str, c) + 1));
    int j = 0;

    if (!clean || !str){
        free(clean);
        return NULL;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            clean[j] = str[i];
            j++;
        }
    }
    clean[j] = '\0';
    return clean;
}
