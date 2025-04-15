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

static int print_on_fd(char *end, int fd)
{
    char *new = NULL;

    my_dputstr(0, "? ");
    new = my_getline();
    if (new == NULL)
        return 0;
    if (my_strcmp(new, end) == 0) {
        free(new);
        return 0;
    }
    my_dputstr(fd, new);
    my_dputstr(fd, "\n");
    free(new);
    return print_on_fd(end, fd);
}

static int next_command(shell_t *shell, command_t *command,
    int prev_fd, int fd[2])
{
    close(fd[1]);
    if (prev_fd != -1)
        close(prev_fd);
    prev_fd = fd[0];
    prev_fd = pipe_command(shell, command, prev_fd);
    if (command->next->next == NULL) {
        close(prev_fd);
        return 0;
    }
    return execute_commands(shell, command->next->next, prev_fd);
}

static int fork_pipe(shell_t *shell, command_t *command,
    int prev_fd, int fd[2])
{
    print_on_fd(command->next->command, fd[1]);
    return next_command(shell, command, prev_fd, fd);
}

int read_to_exec(shell_t *shell, command_t *command, int prev_fd)
{
    int fd[2];

    if (pipe(fd) == -1)
        return EXIT_ERROR;
    return fork_pipe(shell, command, prev_fd, fd);
}
