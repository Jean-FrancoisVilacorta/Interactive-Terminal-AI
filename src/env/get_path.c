/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** path
*/

#include "shell.h"
#include "lib.h"
#include <stdlib.h>
#include <stdio.h>

char **complete_path(char **path)
{
    char *temp = NULL;

    for (size_t i = 0; path[i] != NULL; i++) {
        temp = my_str_cmb(path[i], "/");
        if (temp == NULL) {
            double_free(path);
            return NULL;
        }
        free(path[i]);
        path[i] = temp;
    }
    return path;
}

char **get_path(char const *const *env)
{
    char *all_path = NULL;
    char **path = NULL;

    if (env == NULL)
        return NULL;
    all_path = get_env_data("PATH=", env);
    if (all_path == NULL)
        return NULL;
    path = my_str_to_word_array(all_path, ":\n");
    free(all_path);
    if (path == NULL)
        return NULL;
    return complete_path(path);
}
