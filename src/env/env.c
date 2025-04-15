/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** env
*/

#include "shell.h"
#include "lib.h"
#include <stddef.h>

int print_env(int const fd, char const *const *env)
{
    for (size_t i = 0; env[i] != NULL; i++) {
        if (my_dputstr(fd, env[i]) <= 0)
            return FAIL;
        if (my_dputstr(fd, "\n") <= 0)
            return FAIL;
    }
    return SUCCESS;
}

int env(shell_t *shell, command_t *command)
{
    if (shell == NULL || command == NULL)
        return EXIT_ERROR;
    if (command->ouput != NULL)
        return default_command(shell, command);
    return print_env(1, (char const *const *)(shell->env));
}
