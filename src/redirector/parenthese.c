/*
** EPITECH PROJECT, 2025
** mysh
** File description:
** parenthese
*/

#include <wait.h>
#include "shell.h"

static void execute_parenthese(char *command, int *fd_pipe,
    int *status, char ***env)
{
    char **env_cp = cp_word_arr(*env);
    char *n_com = my_strdup(command);

    if (!env_cp){
        free_word_arr(env_cp);
        close(fd_pipe[READ]);
        close(fd_pipe[WRITE]);
        return;
    }
    if (dup2(fd_pipe[READ], STDIN_FILENO) == FAIL)
        return;
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    *status = exec_all_commands(n_com, &env_cp);
    free_word_arr(env_cp);
    exit(*status);
}

int parenthese(bintree_t *node, char ***env, int *status)
{
    int fd_pipe[2];
    pid_t pid = -1;

    if (!node->left || !node->right)
        return FAIL;
    if (pipe(fd_pipe) == FAIL)
        return FAIL;
    pid = fork();
    if (pid == 0)
        write_in_pipe(node->left, fd_pipe, status, env);
    waitpid(pid, status, 0);
    pid = fork();
    if (pid == 0)
        execute_parenthese((char *)node->right->item, fd_pipe, status, env);
    close(fd_pipe[READ]);
    close(fd_pipe[WRITE]);
    waitpid(pid, status, 0);
    return *status;
}
