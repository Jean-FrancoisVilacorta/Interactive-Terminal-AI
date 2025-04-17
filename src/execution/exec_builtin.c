/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** execute builtin
*/

#include "shell.h"
#include <string.h>
#include <stdio.h>

int exec_builtin(char **comands, char ***env)
{
    for (size_t i = 0; builtin_command[i].name; i++){
        if (!my_strcmp(comands[0], builtin_command[i].name)){
            builtin_command[i].func(env, comands);
            return SUCCESS;
        }
    }
    return FAIL;
}
