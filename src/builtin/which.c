/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** which.c
*/

#include "shell.h"
#include <stdio.h>

int builtin_which(char ***env, char **commands)
{
    // for (size_t i = 0; commands[i] != NULL; ++i)
    //     if (strcmp(commands[i], "-a") == 0)
    //         return print_all_matches(env, commands);
    for (int i = 0; *env[i] != NULL; ++i)
        printf("%s\n", *env[i]);
    commands[0] = strdup(commands[1]);
    printf("%s\n", find_binary(*env, commands));
    return SUCCESS;
}
