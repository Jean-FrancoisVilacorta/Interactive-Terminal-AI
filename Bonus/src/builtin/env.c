/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** env builtin
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

int builtin_env(char ***env)
{
    for (int i = 0; (*env)[i]; i++){
        my_dprintf(STDOUT_FD, "%s\n", (*env)[i]);
    }
    return SUCCESS;
}

int exist_in_env(char ***env, char *commands)
{
    char *variable = get_variable_name(commands);

    if (!variable)
        return FAIL;
    for (int i = 0; (*env)[i]; i++){
        if (!my_strncmp((*env)[i], variable, my_strlen(variable))){
            free(variable);
            return SUCCESS;
        }
    }
    free(variable);
    return FAIL;
}
