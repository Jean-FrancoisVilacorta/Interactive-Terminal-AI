/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** exec command with fork
*/

#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

void print_array(char **array)
{
    for (size_t i = 0; array[i]; i++)
        my_dprintf(0, "[ %s ]\n", array[i]);
}

static char **get_allow_path(char **env)
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

static int binary_in_path(char *comand, char *dir_path)
{
    char *file_path = malloc(sizeof(char) *
        (my_strlen(comand) + my_strlen(dir_path) + 2));

    if (!file_path)
        return FAIL;
    if (my_strncmp(comand, "./", 2) == 0)
        return FAIL;
    file_path[0] = '\0';
    my_strcat(file_path, dir_path);
    my_strcat(file_path, "/");
    my_strcat(file_path, comand);
    if (access(file_path, F_OK) != 0) {
        free(file_path);
        return FAIL;
    }
    free(file_path);
    return SUCCESS;
}

static char *concat_path(char *allow_path, char **commands)
{
    int len = my_strlen(allow_path);
    char *path = malloc(sizeof(char) * (len + my_strlen(commands[0]) + 2));

    path[0] = '\0';
    my_strcat(path, allow_path);
    my_strcat(path, "/");
    return path;
}

static char *find_binary(char **env, char **commands)
{
    char **allow_path = get_allow_path(env);
    char *path = NULL;

    for (size_t i = 0; commands[0][0] != '/' && allow_path[i]; i++){
        if (binary_in_path(commands[0], allow_path[i]) == SUCCESS){
            path = concat_path(allow_path[i], commands);
            break;
        }
    }
    if (!path){
        path = malloc(sizeof(char) * my_strlen(commands[0]));
        if (!path)
            return NULL;
        path[0] = '\0';
    }
    my_strcat(path, commands[0]);
    free_word_arr(allow_path);
    return path;
}

static void child_execute(char **commands, char **env)
{
    char *path = find_binary(env, commands);

    if (!path)
        exit(1);
    if (execve(path, commands, env) == FAIL){
        my_dprintf(STDERR_FD, "%s: Commande introuvable.\n", commands[0]);
        free(path);
        exit(1);
    }
}

static int execute_command(char *command_line, char ***env, int *status)
{
    __pid_t pid = -1;
    char **commands = my_str_to_word_arr(command_line, " \t");

    if (!commands || !commands[0]){
        my_dprintf(STDERR_FD, "failed to get command\n");
        return FAIL;
    }
    if (exec_builtin(commands, env) == SUCCESS)
        return SUCCESS;
    pid = fork();
    if (pid == 0){
        child_execute(commands, (*env));
    }
    free_word_arr(commands);
    waitpid(0, status, 0);
    return print_signal(*status);
}

int execute_tree(bintree_t *tree, char ***env, int *status)
{
    if (!tree || !tree->item)
        return FAIL;
    for (int i = 0; i < NB_REDIRECTOR; i++){
        if (!my_strcmp(redirectors[i].redirector, tree->item)
            && redirectors[i].function){
            return redirectors[i].function(tree, env, status);
        }
    }
    if (execute_command(tree->item, env, status) == FAIL)
        exit(84);
    return *status;
}

int exec_all_commands(char *command_line, char ***env)
{
    int status = 0;
    char **all_commands = my_str_to_word_arr(command_line, ";");
    bintree_t *tree = NULL;

    if (!all_commands || !all_commands[0]){
        my_dprintf(STDERR_FD, "failed to get all_command\n");
        return FAIL;
    }
    for (size_t i = 0; all_commands[i]; i++){
        tree = fill_tree(all_commands[i]);
        if (!tree)
            return 84;
        execute_tree(tree, env, &status);
        free_bintree(tree);
    }
    free_word_arr(all_commands);
    return status;
}
