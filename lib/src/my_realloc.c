/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char *my_realloc(char *str, size_t size)
{
    char *ret = malloc(sizeof(char) * (size + 1));

    if (ret == NULL)
        return NULL;
    if (str == NULL) {
        ret[0] = '\0';
        ret[1] = '\0';
        return ret;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        ret[i] = str[i];
    }
    ret[size - 2] = '\0';
    ret[size - 1] = '\0';
    free(str);
    return ret;
}
