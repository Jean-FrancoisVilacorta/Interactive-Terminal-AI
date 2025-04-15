/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** change_direcotory
*/

#include "shell.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

char *my_str_cmb_pwd(const char *str1, const char *str2)
{
    int long1 = my_strlen(str1);
    int long2 = my_strlen(str2);
    int i = 0;
    char *combined = malloc(sizeof(char) * (long1 + long2 + 2));

    if (combined == NULL)
        return NULL;
    for (i = 0; i < long1; i++) {
        combined[i] = str1[i];
    }
    combined[i] = '/';
    i++;
    for (int j = 0; j < long2; j++) {
        combined[i] = str2[j];
        i++;
    }
    combined[i] = '\0';
    return combined;
}

static char **ouputs(char *type, char *content)
{
    char **ret = malloc(sizeof(char *) * 3);

    if (ret == NULL)
        return NULL;
    ret[0] = my_strcpy(type);
    ret[1] = content;
    return ret;
}

static int change_old_pwd(shell_t *shell)
{
    char **pwd_env = NULL;

    if (get_env_x("OLDPWD", (char const *const *)shell->env) >= 0) {
        pwd_env = ouputs("OLDPWD", shell->oldpwd);
        if (set_env(shell, pwd_env) != SUCCESS) {
            free(pwd_env[0]);
            free(pwd_env);
            return EXIT_ERROR;
        }
        free(pwd_env[0]);
        free(pwd_env);
    }
    return SUCCESS;
}

static int change_new_pwd(shell_t *shell, char *new_pwd)
{
    char **pwd_env = NULL;

    free(shell->oldpwd);
    shell->oldpwd = shell->pwd;
    shell->pwd = new_pwd;
    if (get_env_x("PWD", (char const *const *)shell->env) >= 0) {
        pwd_env = ouputs("PWD", shell->pwd);
        if (set_env(shell, pwd_env) != SUCCESS) {
            free(pwd_env[0]);
            free(pwd_env);
            return EXIT_ERROR;
        }
        free(pwd_env[0]);
        free(pwd_env);
    }
    return change_old_pwd(shell);
}

static int get_clean_pwd(shell_t *shell, char *pwd)
{
    char *new_pwd = NULL;

    free(pwd);
    new_pwd = getcwd(NULL, 0);
    if (new_pwd == NULL) {
        perror("getcwd");
        return STOP_ERROR;
    }
    return change_new_pwd(shell, new_pwd);
}

static int change_directory(shell_t *shell, char *pwd, char *ouput,
    bool free_pwd)
{
    char *new_pwd = NULL;

    if (chdir(pwd) != 0) {
        if (free_pwd == true)
            free(pwd);
        perror(ouput);
        shell->exit = 1;
        return SUCCESS;
    }
    if (free_pwd == false) {
        new_pwd = my_strcpy(pwd);
        return change_new_pwd(shell, new_pwd);
    }
    return get_clean_pwd(shell, pwd);
}

static int create_new_pwd(shell_t *shell, char *add_to_pwd)
{
    int len = my_strlen(shell->pwd);
    char *new_pwd = NULL;

    if (len == 0)
        return STOP_ERROR;
    if (shell->pwd[len - 1] == '/')
        new_pwd = my_str_cmb(shell->pwd, add_to_pwd);
    else
        new_pwd = my_str_cmb_pwd(shell->pwd, add_to_pwd);
    if (new_pwd == NULL)
        return EXIT_ERROR;
    return change_directory(shell, new_pwd, add_to_pwd, true);
}

static int analize_cd(shell_t *shell, command_t *command, int const ac)
{
    if (ac == -1)
        return change_directory(shell, shell->home, shell->home, false);
    if (my_strcmp("-", command->ouput[0]) == 0)
        return change_directory(shell, shell->oldpwd, shell->oldpwd, false);
    if (my_strcmp("~", command->ouput[0]) == 0)
        return change_directory(shell, shell->home, shell->home, false);
    if (command->ouput[0][0] == '/')
        return change_directory(shell, command->ouput[0],
            command->ouput[0], false);
    return create_new_pwd(shell, command->ouput[0]);
}

int cdirectory(shell_t *shell, command_t *command)
{
    int ac = 0;

    if (shell == NULL || command == NULL)
        return STOP_ERROR;
    ac = my_strstrlen((char const *const *)command->ouput);
    if (ac > 1) {
        if (my_dputstr(2, "cd: Too many arguments.\n") < 0)
            return EXIT_ERROR;
        return SUCCESS;
    }
    return analize_cd(shell, command, ac);
}
