/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** unset env variable
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

static int cp_without_variable(char **new, char ***env, char *variable)
{
    int n_index = 0;

    for (int i = 0; (*env)[i]; i++){
        if (!my_strncmp((*env)[i], variable, my_strlen(variable)))
            continue;
        new[n_index] = malloc(sizeof(char) * (my_strlen((*env)[i]) + 1));
        if (!new[n_index])
            return FAIL;
        my_strcpy(new[n_index], (*env)[i]);
        n_index++;
    }
    return SUCCESS;
}

static int remove_from_env(char ***env, char **commands)
{
    char *variable = get_variable_name(commands[1]);
    char **new = malloc(sizeof(char *) * (len_word_arr((*env))));

    if (!new || !variable)
        return FAIL;
    if (cp_without_variable(new, env, variable) == FAIL)
        return FAIL;
    new[len_word_arr((*env)) - 1] = NULL;
    free_word_arr((*env));
    (*env) = cp_word_arr(new);
    free_word_arr(new);
    free(variable);
    return SUCCESS;
}

int builtin_unsetenv(char ***env, char **commands)
{
    if (len_word_arr(commands) != 2)
        return FAIL;
    if (exist_in_env(env, commands[1]) == SUCCESS){
        return remove_from_env(env, commands);
    }
    return FAIL;
}
