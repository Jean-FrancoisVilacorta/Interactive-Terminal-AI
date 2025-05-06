/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** where.c
*/

#include "shell.h"
#include <stdio.h>

static void print_builtin(const char *cmd)
{
    if (strcmp(cmd, "env") == 0)
        return;
    for (size_t i = 0; builtin_command[i].name != NULL; ++i)
        if (strcmp(cmd, builtin_command[i].name) == 0) {
            printf("%s is a shell built-in\n", builtin_command[i].name);
            return;
        }
}

int builtin_where(char ***env, char **commands)
{
    if (!commands[1]) {
        dprintf(STDERR_FD, "where: Too few arguments.\n");
        return FAIL;
    }
    for (size_t i = 1; commands[i] != NULL; ++i) {
        print_match(env, commands[i], false);
        print_builtin(commands[i]);
    }
    return SUCCESS;
}
