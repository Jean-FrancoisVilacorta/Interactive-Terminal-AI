/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** default_data
*/

#include "lib.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static const char default_path[] =
"/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin:/usr/local/sbin";

static char **complete_path(char **path)
{
    char *temp = NULL;

    for (size_t i = 0; path[i] != NULL; i++) {
        temp = my_str_cmb(path[i], "/");
        if (temp == NULL) {
            double_free(path);
            return NULL;
        }
        free(path[i]);
        path[i] = temp;
    }
    return path;
}

static char **get_defaulth_path(void)
{
    char **path = NULL;

    path = my_str_to_word_array(default_path, ":\n");
    if (path == NULL)
        return NULL;
    return complete_path(path);
}

static int error_case(shell_t *shell)
{
    if (shell->pwd == NULL || shell->oldpwd == NULL ||
        shell->home == NULL || shell->path == NULL) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    return SUCCESS;
}

static char *create_path_home(char **path, char *result)
{
    char *home = NULL;
    char *temp = NULL;

    temp = my_str_cmb(result, "/");
    if (temp == NULL) {
        double_free(path);
        return my_strcpy("/home");
    }
    home = my_str_cmb(temp, path[1]);
    double_free(path);
    free(temp);
    return home;
}

static char *cut_home(char *pwd)
{
    char **temp = my_str_to_word_array(pwd, "/");
    char *result = NULL;

    if (temp == NULL)
        return NULL;
    if (temp[0] == NULL) {
        double_free(temp);
        return my_strcpy("/home");
    }
    if (temp[1] == NULL) {
        double_free(temp);
        return my_strcpy("/home");
    }
    result = my_str_cmb("/", temp[0]);
    if (result == NULL)
        return NULL;
    return create_path_home(temp, result);
}

static int default_case(shell_t *shell)
{
    if (shell->pwd == NULL)
        shell->pwd = getcwd(NULL, 0);
    if (shell->oldpwd == NULL)
        shell->oldpwd = getcwd(NULL, 0);
    if (shell->home == NULL)
        shell->home = cut_home(shell->pwd);
    if (shell->path == NULL)
        shell->path = get_defaulth_path();
    return error_case(shell);
}

int default_info(shell_t *shell, char const *const *env)
{
    shell->pwd = get_env_data("PWD=", (char const *const *)shell->env);
    shell->oldpwd = get_env_data("OLDPWD=", (char const *const *)shell->env);
    shell->home = get_env_data("HOME=", (char const *const *)shell->env);
    shell->path = get_path(env);
    shell->dividers = NULL;
    shell->exit = 0;
    return default_case(shell);
}
