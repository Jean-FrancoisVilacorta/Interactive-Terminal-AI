/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** copies an string into another
*/

#include <stddef.h>
#include <stdlib.h>
#include "my_getline.h"

static char *copy_content_skip(char const *str, char *cpy, int const skip)
{
    size_t x = 0;

    while (str[x + skip] != '\0') {
        cpy[x] = str[x + skip];
        x++;
    }
    cpy[x] = '\0';
    return cpy;
}

char *my_skip_strcpy(char const *str, int const skip)
{
    int len = my_strlen(str) - skip;
    char *cpy = NULL;

    if (str == NULL)
        return NULL;
    cpy = malloc(sizeof(char) * (len + 1));
    if (cpy == NULL)
        return NULL;
    return copy_content_skip(str, cpy, skip);
}

static char *copy_content(char const *str, char *cpy)
{
    size_t x = 0;

    while (str[x] != '\0') {
        cpy[x] = str[x];
        x++;
    }
    cpy[x] = '\0';
    return cpy;
}

char *my_strcpy(char const *str)
{
    int len = my_strlen(str);
    char *cpy = NULL;

    if (str == NULL)
        return NULL;
    cpy = malloc(sizeof(char) * (len + 1));
    if (cpy == NULL)
        return NULL;
    return copy_content(str, cpy);
}
