/*
** EPITECH PROJECT, 2025
** shell
** File description:
** pipe
*/

#include "shell.h"
#include <wait.h>

void write_in_pipe(bintree_t *tree, int *fd_pipe,
    int *status, char ***env)
{
    if (dup2(fd_pipe[WRITE], STDOUT_FILENO) == FAIL)
        return;
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    if (my_strcmp(tree->item, "")){
        *status = execute_tree(tree, env, status);
    }
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
    pid_t pid_one = -1;
    pid_t pid_two = -1;

    if (!node->left || !node->right)
        return FAIL;
    if (pipe(fd_pipe) == FAIL)
        return FAIL;
    pid_one = fork();
    if (pid_one == 0)
        write_in_pipe(node->left, fd_pipe, status, env);
    pid_two = fork();
    if (pid_two == 0)
        execute_com_end(node->right, fd_pipe, status, env);
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    waitpid(pid_one, status, 0);
    waitpid(pid_two, status, 0);
    return *status;
}
