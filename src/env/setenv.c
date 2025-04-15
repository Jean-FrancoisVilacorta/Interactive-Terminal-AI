/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** setenv
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "lib.h"

static char **cpy_content(char **cpy, char const *const *strstr)
{
    size_t x = 0;

    while (strstr[x] != NULL) {
        cpy[x] = my_strcpy(strstr[x]);
        if (cpy[x] == NULL)
            return NULL;
        x++;
    }
    cpy[x] = NULL;
    cpy[x + 1] = NULL;
    return cpy;
}

static char **my_strstrcpy_more(char const *const *strstr)
{
    int len = my_strstrlen(strstr);
    char **cpy = NULL;

    if (strstr == NULL)
        return NULL;
    cpy = malloc(sizeof(char *) * (len + 2));
    if (cpy == NULL)
        return NULL;
    return cpy_content(cpy, strstr);
}

static int change_content(char **env, char **ouputs, int x)
{
    char *temp = my_str_cmb(ouputs[0], "=");

    free(env[x]);
    if (ouputs[1] == NULL) {
        env[x] = temp;
        return SUCCESS;
    }
    env[x] = my_str_cmb(temp, ouputs[1]);
    free(temp);
    return SUCCESS;
}

static int add_new(shell_t *shell, char **ouputs, char **env)
{
    char **new_env = my_strstrcpy_more((char const *const *)env);
    int len = 0;

    if (new_env == NULL) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    double_free(env);
    len = my_strstrlen((char const *const *)new_env);
    shell->env = new_env;
    return change_content(new_env, ouputs, len);
}

int set_env(shell_t *shell, char **ouputs)
{
    int x = get_env_x(ouputs[0], (char const *const *)shell->env);

    if (x == -2)
        return EXIT_ERROR;
    if (x == -1) {
        return add_new(shell, ouputs, shell->env);
    }
    return change_content(shell->env, ouputs, x);
}

int my_setenv(shell_t *shell, command_t *command)
{
    int ac = my_strstrlen((char const *const *)command->ouput);

    if (ac > 2) {
        my_dputstr(2, "setenv: Too many arguments.\n");
        return SUCCESS;
    }
    if (ac <= 0)
        return print_env(1, (char const *const *)shell->env);
    if (set_env(shell, command->ouput) == EXIT_ERROR) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    return SUCCESS;
}
