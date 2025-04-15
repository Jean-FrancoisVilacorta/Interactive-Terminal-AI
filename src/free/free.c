/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** free
*/

#include <stddef.h>
#include <stdlib.h>
#include "shell.h"

void double_free(char **array)
{
    if (array == NULL)
        return;
    for (size_t i = 0; array[i] != NULL; i++) {
        if (array[i] != NULL)
            free(array[i]);
    }
    free(array);
}

void free_commands(command_t *commands)
{
    if (commands == NULL)
        return;
    double_free(commands->ouput);
    if (commands->command != NULL)
        free(commands->command);
    if (commands->flag != NULL)
        free(commands->flag);
    free_commands(commands->next);
    free(commands);
}

void free_dividers(dividers_t *div)
{
    if (div == NULL)
        return;
    if (div->flag != NULL)
        free(div->flag);
    free_commands(div->commands);
    free_dividers(div->next);
    free(div);
}

void free_shell(shell_t *shell)
{
    if (shell == NULL)
        return;
    double_free(shell->env);
    double_free(shell->path);
    if (shell->home != NULL)
        free(shell->home);
    if (shell->pwd != NULL)
        free(shell->pwd);
    if (shell->oldpwd != NULL)
        free(shell->oldpwd);
    if (shell->dividers != NULL)
        free_dividers(shell->dividers);
    free(shell);
}
