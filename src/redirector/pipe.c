/*
** EPITECH PROJECT, 2025
** shell
** File description:
** pipe
*/

#include "shell.h"
#include <wait.h>

static void execute_com(bintree_t *tree, int *fd_pipe,
    int *status, char ***env)
{
    if (dup2(fd_pipe[WRITE], STDOUT_FILENO) == FAIL)
        return;
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    *status = execute_tree(tree, env, status);
    exit(*status);
}

static void execute_com_end(bintree_t *tree, int *fd_pipe,
    int *status, char ***env)
{
    if (dup2(fd_pipe[READ], STDIN_FILENO) == FAIL)
        return;
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    *status = execute_tree(tree, env, status);
    exit(*status);
}

int my_pipe(bintree_t *node, char ***env, int *status)
{
    int fd_pipe[2];
    pid_t pid = -1;

    if (!node->left || !node->right)
        return FAIL;
    if (pipe(fd_pipe) == FAIL)
        return FAIL;
    pid = fork();
    if (pid == 0)
        execute_com(node->left, fd_pipe, status, env);
    waitpid(pid, status, 0);
    pid = fork();
    if (pid == 0)
        execute_com_end(node->right, fd_pipe, status, env);
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    waitpid(pid, status, 0);
    return *status;
}
