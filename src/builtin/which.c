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

void find_all_matches(char *cmd, char **dirs, int *found,
    bool is_which)
{
    char *path = NULL;

    for (size_t i = 0; cmd[0] != '\0' &&
        cmd[0] != '/' && dirs[i]; i++) {
        *found = binary_in_path(cmd, dirs[i]);
        if (*found == SUCCESS && is_which) {
            path = concat_path(dirs[i], cmd);
            my_strcat(path, cmd);
            printf("%s\n", path);
            break;
        }
        if (*found == SUCCESS && !is_which) {
            path = concat_path(dirs[i], cmd);
            my_strcat(path, cmd);
            printf("%s\n", path);
        }
    }
}

int print_match(char ***env, char *command, bool is_which)
{
    char **dirs = NULL;
    int found = 0;

    dirs = get_path_vars(*env);
    if (!dirs)
        return FAIL;
    find_all_matches(command, dirs, &found, is_which);
    if (found)
        return FAIL;
    free_word_arr(dirs);
    return SUCCESS;
}

static void print_builtin_match(const char *cmd)
{
    if (strcmp(cmd, "env") == 0)
        return;
    for (size_t i = 0; builtin_command[i].name != NULL; ++i)
        if (strcmp(cmd, builtin_command[i].name) == 0) {
            printf("%s: shell built-in command.\n", builtin_command[i].name);
            return;
        }
}

int builtin_which(char ***env, char **commands)
{
    if (!commands[1]) {
        dprintf(STDERR_FD, "which: Too few arguments.\n");
        return FAIL;
    }
    for (size_t i = 1; commands[i] != NULL; ++i) {
        print_match(env, commands[i], true);
        print_builtin_match(commands[i]);
    }
    return SUCCESS;
}
