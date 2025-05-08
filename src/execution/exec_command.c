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
#include <ctype.h>

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

int binary_in_path(char *cmd, char *dir)
{
    char *path = malloc(sizeof(char) *
        (my_strlen(cmd) + my_strlen(dir) + 2));

    if (!path)
        return FAIL;
    path[0] = '\0';
    my_strcat(path, dir);
    my_strcat(path, "/");
    my_strcat(path, cmd);
    if (check_file_access(path) == EXIT_FAILURE) {
        free(path);
        return FAIL;
    }
    free(path);
    return SUCCESS;
}

char *concat_path(char *dir, char *cmd)
{
    int len = my_strlen(dir);
    char *path = malloc(sizeof(char) * (len + my_strlen(cmd) + 2));

    if (!path)
        return NULL;
    path[0] = '\0';
    my_strcat(path, dir);
    my_strcat(path, "/");
    return path;
}

static char *find_in_path(char **cmds, char **dirs, int *found)
{
    char *path = NULL;

    for (size_t i = 0; cmds[0][0] != '\0' &&
        cmds[0][0] != '/' && dirs[i]; i++) {
        *found = binary_in_path(cmds[0], dirs[i]);
        if (*found == SUCCESS) {
            path = concat_path(dirs[i], cmds[0]);
            break;
        }
    }
    return path;
}

static char *find_binary(char **env, char **cmds)
{
    char **dirs = NULL;
    char *path = NULL;
    int found = 0;

    if (is_direct_path(cmds[0]))
        return handle_direct_binary(cmds[0]);
    dirs = get_allow_path(env);
    path = find_in_path(cmds, dirs, &found);
    if (found == FAIL)
        my_dprintf(STDERR_FD, "%s: Command not found.\n", cmds[0]);
    if (!path)
        path = handle_command_not_exist(cmds[0]);
    my_strcat(path, cmds[0]);
    free_word_arr(dirs);
    return path;
}

static void child_execute(char **cmds, char **env)
{
    char *path = find_binary(env, cmds);

    for (int i = 0; cmds[i]; i++){
        if (have_inhibitor(cmds[i]) == FAIL){
            exit(1);
        }
    }
    cmds = find_globbings(cmds);
    if (!path || !cmds)
        exit(1);
    if (execve(path, cmds, env) == FAIL) {
        free(path);
        exit(1);
    }
}

static int execute_command(char *line, char ***env, int *status)
{
    pid_t pid;
    char **cmds = NULL;
    int background = is_background(line);

    line = trim_background(line);
    cmds = split_command_line(line, " \t\r\n");
    if (!cmds || !cmds[0])
        return FAIL;
    if (exec_builtin(cmds, env) == SUCCESS)
        return SUCCESS;
    pid = fork();
    if (pid == 0)
        child_execute(cmds, *env);
    if (background) {
        add_job(get_jobs_list(), pid, line);
        return SUCCESS;
    }
    free_word_arr(cmds);
    waitpid(pid, status, 0);
    return print_signal(*status);
}

int execute_tree(bintree_t *tree, char ***env, int *status)
{
    if (!tree || !tree->item)
        return FAIL;
    for (int i = 0; i < NB_REDIRECTOR; i++) {
        if (!my_strcmp(redirectors[i].redirector, tree->item)
            && redirectors[i].function)
            return redirectors[i].function(tree, env, status);
    }
    if (execute_command(tree->item, env, status) == FAIL)
        *status = 84;
    return *status;
}

char *check_builtin_in_pipe(char *cmd)
{
    char **arr = my_str_to_word_arr(cmd, "|");
    size_t len = my_array_len(arr);

    if (!arr || !len)
        return cmd;
    for (size_t i = 0; builtin_command[i].name; i++) {
        if (strstr(arr[len - 1], builtin_command[i].name))
            return arr[len - 1];
    }
    return cmd;
}

int exec_all_commands(char *line, char ***env)
{
    char **cmds = my_str_to_word_arr_ignore(line, ";");
    bintree_t *tree = NULL;
    int status = is_command_valid(cmds);

    if (status != 0)
        return status;
    for (size_t i = 0; cmds[i]; i++) {
        cmds[i] = check_builtin_in_pipe(cmds[i]);
        cmds[i] = is_an_alias(cmds[i]);
        cmds[i] = dollars_signe(env, cmds[i]);
        tree = fill_tree(cmds[i]);
        if (!tree)
            return 84;
        execute_tree(tree, env, &status);
        free_bintree(tree);
    }
    free_word_arr(cmds);
    return status;
}
