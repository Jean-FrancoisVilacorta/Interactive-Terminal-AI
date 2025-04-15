/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** redirect_pipe
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "lib.h"
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static int read_case(shell_t *shell, command_t *command,
    int fd[2])
{
    int status = 0;

    if (command->next->next != NULL)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    status = run_prog(shell, command);
    return status;
}

static int exec_pipe_command(shell_t *shell, command_t *command,
    int prev_fd, int fd[2])
{
    int status = 0;

    if (prev_fd != -1) {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (command->flag != NULL)
        if (my_strcmp("<<", command->flag) == 0)
            return read_case(shell, command, fd);
    if (command->next != NULL)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    status = run_prog(shell, command);
    return status;
}

static int fork_pipe(shell_t *shell, command_t *command,
    int prev_fd, int fd[2])
{
    pid_t status = 0;
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_ERROR;
    }
    if (pid == 0)
        exit(exec_pipe_command(shell, command, prev_fd, fd));
    waitpid(pid, &status, 0);
    close(fd[1]);
    if (prev_fd != -1)
        close(prev_fd);
    prev_fd = fd[0];
    if (status == -1)
        return EXIT_ERROR;
    return error_wait(status, shell, command, prev_fd);
}

int pipe_command(shell_t *shell, command_t *command, int prev_fd)
{
    int fd[2];

    if (pipe(fd) == -1)
        return EXIT_ERROR;
    return fork_pipe(shell, command, prev_fd, fd);
}
