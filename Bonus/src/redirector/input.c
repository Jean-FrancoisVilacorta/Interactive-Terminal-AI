/*
** EPITECH PROJECT, 2025
** shell
** File description:
** redirect input
*/

#include "shell.h"
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int redirect_input(bintree_t *node, char ***env, int *status)
{
    __pid_t pid = -1;
    int file = open((char *)node->right->item, O_RDONLY);

    pid = fork();
    if (pid == 0){
        dup2(file, STDIN_FILENO);
        close(file);
        *status = execute_tree(node->left, env, status);
        exit(84);
    }
    waitpid(pid, NULL, 0);
    close(file);
    return *status;
}
