/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** is_binary
*/

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int is_direct_path(char *cmd)
{
    return !!strchr(cmd, '/');
}

char *handle_direct_binary(char *cmd)
{
    if (check_file_access(cmd) == FAIL)
        return NULL;
    if (check_basic_access(cmd) == EXIT_FAILURE)
        return NULL;
    return my_strdup(cmd);
}

char *handle_command_not_exist(char *cmd)
{
    char *res = malloc(sizeof(char) * (my_strlen(cmd) + 1));

    if (!res)
        return NULL;
    res[0] = '\0';
    my_strcat(res, cmd);
    return res;
}
