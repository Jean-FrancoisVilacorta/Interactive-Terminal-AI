/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** amazed
*/

#include "my_getline.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static void free_strstr(char **arr)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; arr[i] != NULL; i++) {
        if (arr[i] != NULL)
            free(arr[i]);
    }
    free(arr);
}

static char **remove_p2(char **arr, size_t len)
{
    char **new = malloc(sizeof(char *) * (len));

    for (size_t i = 0; arr[i + 1] != NULL; i++) {
        new[i] = arr[i];
    }
    free(arr);
    new[len - 1] = NULL;
    return new;
}

char **remove_line(char **arr)
{
    size_t len = my_strstrlen(arr);

    if (arr == NULL)
        return NULL;
    if (len == 1) {
        free_strstr(arr);
        return NULL;
    }
    return remove_p2(arr, len);
}

char **add_new_line(char **arr, char *new_str)
{
    size_t len = my_strstrlen(arr);
    char **new = malloc(sizeof(char *) * (len + 2));

    if (new == NULL)
        return NULL;
    for (size_t x = 0; x != len; x++)
        new[x] = arr[x];
    new[len] = new_str;
    new[len + 1] = NULL;
    if (arr != NULL)
        free(arr);
    return new;
}
