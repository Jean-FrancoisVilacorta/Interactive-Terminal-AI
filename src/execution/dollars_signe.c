/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** $$$
*/

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

size_t my_strnlen(char const *str, size_t n)
{
    size_t i = 0;

    for (i = 0; str[i] && i < n; i++);
    return i;
}

char *get_dollars_env(char ***env, char *value, size_t len, char *line)
{
    size_t len_var = 0;
    char *command = NULL;
    char *variable = NULL;

    value = (!strcmp(value, "$")) ? value : clean_str(value, '$');
    variable = get_env_variable(*env, value);
    if (!variable) {
        dprintf(2, "%s: Undefined variable.\n", value);
        return NULL;
    }
    variable += (strlen(value) + 1);
    len_var = strlen(variable);
    command = malloc(len_var + len + 1);
    if (!command)
        return NULL;
    strncpy(command, line, len);
    strcat(command, variable);
    return command;
}

char *dollars_signe(char ***env, char *line)
{
    char *value = strstr(line, "$");
    size_t index = value - line;
    size_t len = my_strnlen(line, index);

    if (!value)
        return line;
    return get_dollars_env(env, value, len, line);
}
