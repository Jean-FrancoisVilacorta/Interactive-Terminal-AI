/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** cd builtin
*/

#include "shell.h"
#include <stdio.h>
#include <unistd.h>


static int get_len_new_path(char **actual, char **take)
{
    int len = len_word_arr(actual);

    for (int i = 0; take[i]; i++){
        if (!my_strcmp("..", take[i]))
            len--;
        else
            len++;
    }
    return len;
}

static char *concat_new_path(char **path)
{
    int len = 0;
    char *new_path = NULL;

    if (!path)
        return NULL;
    for (int i = 0; path[i]; i++)
        len += my_strlen(path[i]) + 1;
    new_path = malloc(sizeof(char) * (len + 2));
    new_path[0] = '\0';
    my_strcat(new_path, "/");
    for (int i = 0; path[i]; i++){
        my_strcat(new_path, path[i]);
        my_strcat(new_path, "/");
    }
    new_path[len] = '\0';
    free_word_arr(path);
    return new_path;
}

static void fill_new_path(char **new, char **actual, char **take)
{
    int i = 0;

    while (actual[i]){
        new[i] = malloc(sizeof(char) * (my_strlen(actual[i]) + 1));
        my_strcpy(new[i], actual[i]);
        i++;
    }
    for (int j = 0; take[j]; j++){
        if (!my_strcmp("..", take[j])){
            free(new[i - 1]);
            i--;
        } else {
            new[i] = malloc(sizeof(char) * (my_strlen(take[j]) + 1));
            my_strcpy(new[i], take[j]);
            i++;
        }
    }
}

static char *find_new_path(char *actual, char *to_take)
{
    char **actual_path = my_str_to_word_arr(actual, "/");
    char **path_to_take = my_str_to_word_arr(to_take, "/");
    int len_new_path = get_len_new_path(actual_path, path_to_take);
    char **new_path = malloc(sizeof(char *) * (len_new_path + 1));

    fill_new_path(new_path, actual_path, path_to_take);
    new_path[len_new_path] = NULL;
    free_word_arr(path_to_take);
    return concat_new_path(new_path);
}

static void set_old_pwd(char ***env, char *pwd)
{
    char *oldpwd[4] = {"setenv", "OLDPWD", pwd, NULL};

    builtin_setenv(env, oldpwd);
}

static void set_new_pwd(char ***env, char *pwd)
{
    char *new_path[4] = {"setenv", "PWD", pwd, NULL};

    builtin_setenv(env, new_path);
}

static int print_fd_error(char *path)
{
    my_dprintf(STDERR_FD, "%s: No such file or directory.\n", path);
    return 1;
}

static int print_not_d(char *path)
{
    my_dprintf(STDERR_FD, "%s: Not a directory.\n", path);
    return 1;
}

static char *get_new_path(char ***env, char *path, char *old_path)
{
    char *new_path = NULL;

    if (path[0] == '/') {
        new_path = malloc(sizeof(char) * (my_strlen(path) + 1));
        my_strcpy(new_path, path);
    } else if (!my_strcmp(path, "-")) {
        new_path = get_env_variable((*env), "OLDPWD=") + 7;
    } else
        new_path = find_new_path(old_path, path);
    return new_path;
}

int builtin_cd(char ***env, char **commands)
{
    char *new_path = NULL;
    char *old_path = getcwd(NULL, 0);

    if (len_word_arr(commands) > 2)
        return FAIL;
    if (len_word_arr(commands) == 1) {
        new_path = get_env_variable((*env), "HOME=") + 5;
    } else
        new_path = get_new_path(env, commands[1], old_path);
    if (chdir(new_path) == FAIL) {
        if (access(new_path, F_OK) == 0) {
            return print_not_d(commands[1]);
        } else
            return print_fd_error(commands[1]);
    } else {
        set_new_pwd(env, new_path);
        set_old_pwd(env, old_path);
    }
    return SUCCESS;
}
