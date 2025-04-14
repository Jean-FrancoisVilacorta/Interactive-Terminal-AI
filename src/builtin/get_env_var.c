/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** get env variable from command
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

char *get_env_variable(char **env, char *name)
{
    char *variable = NULL;

    for (int i = 0; env[i]; i++){
        if (!my_strncmp(name, env[i], my_strlen(name))){
            variable = malloc(sizeof(char) * (my_strlen(env[i]) + 1));
            my_strcpy(variable, env[i]);
            variable[my_strlen(env[i])] = '\0';
            break;
        }
    }
    return variable;
}

char *get_variable_name(char *commands)
{
    char *variable = NULL;

    variable = malloc(sizeof(char) * (my_strlen(commands) + 2));
    if (!variable)
        return NULL;
    variable[0] = '\0';
    my_strcat(variable, commands);
    my_strcat(variable, "=");
    variable[my_strlen(commands) + 1] = '\0';
    return variable;
}

char *get_variable_from_command(char **commands)
{
    char *var = malloc(sizeof(char) *
        (my_strlen(commands[1]) + my_strlen(commands[2]) + 2));

    if (!var)
        return NULL;
    var[0] = '\0';
    my_strcat(var, commands[1]);
    my_strcat(var, "=");
    if (commands[2])
        my_strcat(var, commands[2]);
    var[my_strlen(commands[1]) + my_strlen(commands[2]) + 1] = '\0';
    return var;
}
