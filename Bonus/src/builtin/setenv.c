/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** setenv
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int replace_env(char ***env, char **command, int line)
{
    int len = my_strlen(command[1]) + my_strlen(command[2]) + 1;

    free((*env)[line]);
    (*env)[line] = malloc(sizeof(char) * (len + 1));
    if (!(*env)[line]){
        return FAIL;
    }
    (*env)[line] = get_variable_from_command(command);
    return SUCCESS;
}

char **concat_word_arr(char **arr, char **comands)
{
    int size = len_word_arr(arr);
    int i = 0;
    char **new_arr = malloc(sizeof(char *) * (size + 2));

    while (arr[i]){
        new_arr[i] = malloc(sizeof(char) * (my_strlen(arr[i]) + 1));
        if (!new_arr[i])
            return NULL;
        new_arr[i][0] = '\0';
        my_strcpy(new_arr[i], arr[i]);
        i++;
    }
    new_arr[i] = get_variable_from_command(comands);
    new_arr[i + 1] = NULL;
    return new_arr;
}

static int add_env(char ***env, char **command)
{
    char **n_env = concat_word_arr((*env), command);

    free_word_arr((*env));
    (*env) = cp_word_arr(n_env);
    free_word_arr(n_env);
    return SUCCESS;
}

int is_valid_env_name(const char *name)
{
    if (!name || !*name || (*name >= '0' && *name <= '9')) {
        my_dprintf(STDERR_FD, "setenv: "
            "Variable name must begin with a letter.\n");
        return FAIL;
    }
    for (int i = 0; name[i]; i++) {
        if (!(name[i] == '_' ||
            (name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= 'A' && name[i] <= 'Z') ||
            (i > 0 && name[i] >= '0' && name[i] <= '9'))) {
            my_dprintf(2, "setenv: Variable name must contain "
                "alphanumeric characters.\n");
            return FAIL;
        }
    }
    return SUCCESS;
}

int builtin_setenv(char ***env, char **commands)
{
    char *variable = NULL;
    int nb_command = len_word_arr(commands);

    if (nb_command == 1) {
        builtin_env(env);
        return SUCCESS;
    }
    if (nb_command > 3 || nb_command <= 1 ||
        is_valid_env_name(commands[1]) == FAIL)
        return FAIL;
    variable = get_variable_name(commands[1]);
    for (int i = 0; (*env)[i]; i++){
        if (!my_strncmp((*env)[i], variable, my_strlen(variable))){
            return replace_env(env, commands, i);
        }
    }
    return add_env(env, commands);
}
