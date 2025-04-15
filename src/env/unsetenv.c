/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** unsetenv
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "lib.h"

static char **deplace_x(char **env, int x)
{
    int len = my_strstrlen((char const *const *)env);
    char **cpy = malloc(sizeof(char *) * (len + 1));
    size_t a = 0;

    for (int i = 0; env[i] != NULL; i++) {
        if (i != x) {
            cpy[a] = env[i];
            a++;
        }
    }
    cpy[a] = NULL;
    free(env[x]);
    free(env);
    return cpy;
}

static int delete_this(shell_t *shell, char const *str)
{
    int x = get_env_x(str, (char const *const *)shell->env);

    if (x == -2)
        return EXIT_ERROR;
    if (x == -1)
        return SUCCESS;
    shell->env = deplace_x(shell->env, x);
    if (shell->env == NULL)
        return EXIT_ERROR;
    return SUCCESS;
}

int my_unsetenv(shell_t *shell, command_t *command)
{
    int ac = my_strstrlen((char const *const *)command->ouput);

    if (ac < 1) {
        my_dputstr(2, "unsetenv: Too few arguments\n");
        return SUCCESS;
    }
    for (size_t i = 0; command->ouput[i] != NULL; i++) {
        if (delete_this(shell, command->ouput[i]) == EXIT_ERROR) {
            free_shell(shell);
            return EXIT_ERROR;
        }
    }
    return SUCCESS;
}
