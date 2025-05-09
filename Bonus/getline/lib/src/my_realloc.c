/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my_getline.h"

static char *make_bigger(char *str, size_t size)
{
    char *ret = malloc(sizeof(char) * (size + 2));
    size_t x = 0;

    if (ret == NULL)
        return NULL;
    if (str != NULL) {
        while (str[x] != '\0') {
            ret[x] = str[x];
            x++;
        }
    }
    ret[x] = '\0';
    ret[x + 1] = '\0';
    return ret;
}

char *my_realloc(char *str)
{
    size_t size = 0;
    char *ret = NULL;

    if (str != NULL)
        size = my_strlen(str);
    ret = make_bigger(str, size);
    if (str != NULL)
        free(str);
    return ret;
}
