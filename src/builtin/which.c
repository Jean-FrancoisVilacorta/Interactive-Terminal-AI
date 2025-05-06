/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** which.c
*/

#include "shell.h"
#include <stdio.h>

static char **get_path_vars(char **env)
{
    char *path_variable = NULL;
    char **allow_path = NULL;

    if (exist_in_env(&env, "PATH") == FAIL)
        return NULL;
    path_variable = get_env_variable(env, "PATH=");
    path_variable += 5;
    allow_path = my_str_to_word_arr(path_variable, ":");
    path_variable -= 5;
    free(path_variable);
    return allow_path;
}

static void find_all_matches(char **cmds, char **dirs, int *found)
{
    char *path = NULL;

    for (size_t i = 0; cmds[0][0] != '\0' &&
        cmds[0][0] != '/' && dirs[i]; i++) {
        *found = binary_in_path(cmds[2], dirs[i]);
        if (*found == SUCCESS) {
            path = concat_path(dirs[i], cmds);
            my_strcat(path, cmds[2]);
            printf("%s\n", path);
        }
    }
}

static int print_all_matches(char ***env, char **commands)
{
    char **dirs = NULL;
    int found = 0;

    dirs = get_path_vars(*env);
    if (!dirs)
        return FAIL;
    find_all_matches(commands, dirs, &found);
    if (found)
        return FAIL;
    free_word_arr(dirs);
    return SUCCESS;
}

int builtin_which(char ***env, char **commands)
{
    if (strcmp(commands[1], "-a") == 0) {
        if (!commands[2])
            return FAIL;
        return print_all_matches(env, commands);
    }
    commands[0] = strdup(commands[1]);
    if (!commands[0])
        return FAIL;
    printf("%s\n", find_binary(*env, commands));
    return SUCCESS;
}
