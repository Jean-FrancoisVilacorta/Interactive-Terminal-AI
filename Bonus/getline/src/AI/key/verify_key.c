/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** verify_key
*/

#include "gpt.h"
#include "my_getline.h"
#include <stdlib.h>

static char *get_history_patha(void)
{
    char *home = getenv("HOME");
    char *str = my_str_cmb(home, "/.API_KEY");

    return str;
}

char *verify_key(void)
{
    char *path = get_history_patha();
    char *file = NULL;

    if (path == NULL)
        return NULL;
    file = open_file(path);
    if (file == NULL)
        return create_api_key(path);
    free(path);
    return file;
}
