/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** my_strstrcpy
*/

#include <stddef.h>
#include <stdlib.h>
#include "my_getline.h"

static char **cpy_content(char **cpy, char **strstr)
{
    size_t x = 0;

    while (strstr[x] != NULL) {
        cpy[x] = my_strcpy(strstr[x]);
        if (cpy[x] == NULL)
            return NULL;
        x++;
    }
    cpy[x] = NULL;
    return cpy;
}

char **my_strstrcpy(char **strstr)
{
    int len = my_strstrlen(strstr);
    char **cpy = NULL;

    if (strstr == NULL)
        return NULL;
    cpy = malloc(sizeof(char *) * (len + 1));
    if (cpy == NULL)
        return NULL;
    return cpy_content(cpy, strstr);
}
