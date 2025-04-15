/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** redirect_to_file
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
#include <fcntl.h>

static int exec_pipe_command(shell_t *shell, command_t *command,
    int prev_fd, int fd)
{
    int status = 0;

    prev_fd = prev_fd;
    dup2(fd, STDIN_FILENO);
    close(fd);
    if (command->next != NULL)
        dup2(fd, STDOUT_FILENO);
    status = run_prog(shell, command);
    return status;
}

static int fork_pipe(shell_t *shell, command_t *command,
    int prev_fd, int fd)
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
    if (prev_fd != -1)
        close(prev_fd);
    prev_fd = fd;
    if (status == -1)
        return EXIT_ERROR;
    return error_wait(status, shell, command->next, prev_fd);
}

int send_file_to_exec(shell_t *shell, command_t *command,
    int prev_fd)
{
    int fd = open(command->next->command, O_RDONLY);

    if (fd == -1)
        return error_wait(0, shell, command->next, 1);
    return fork_pipe(shell, command, prev_fd, fd);
}
