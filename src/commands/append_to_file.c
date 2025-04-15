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

    if (prev_fd != -1) {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
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

int redirect_to_file_and_append(shell_t *shell,
    command_t *command, int prev_fd)
{
    int fd = open(command->next->command, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror(command->next->command);
        return (EXIT_ERROR);
    }
    return fork_pipe(shell, command, prev_fd, fd);
}
