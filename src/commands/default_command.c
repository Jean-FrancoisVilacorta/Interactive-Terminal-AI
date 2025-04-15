/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** default_command
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

static char **cpy_content(char **cpy, char **strstr)
{
    size_t x = 1;

    while (strstr[x - 1] != NULL) {
        cpy[x] = my_strcpy(strstr[x - 1]);
        if (cpy[x] == NULL)
            return NULL;
        x++;
    }
    cpy[x] = NULL;
    return cpy;
}

static char **my_strstrcpy_path(char **strstr)
{
    int len = my_strstrlen((char const *const *)strstr);
    char **cpy = NULL;

    if (strstr == NULL) {
        cpy = malloc(sizeof(char *) * 2);
        cpy[1] = NULL;
        return cpy;
    }
    cpy = malloc(sizeof(char *) * (len + 2));
    if (cpy == NULL)
        return NULL;
    return cpy_content(cpy, strstr);
}

int run_prog(shell_t *shell, command_t *command)
{
    char **argv = my_strstrcpy_path(command->ouput);

    if (argv == NULL)
        return 84;
    argv[0] = my_str_cmb_pwd(shell->pwd, command->command);
    if (argv[0] == NULL)
        return 84;
    if (execve(argv[0], argv, shell->env) == 0)
        return SUCCESS;
    free(argv[0]);
    for (size_t i = 1; shell->path[i] != NULL; i++) {
        argv[0] = my_str_cmb(shell->path[i], command->command);
        if (argv[0] == NULL)
            return 84;
        execve(argv[0], argv, shell->env);
        free(argv[0]);
    }
    my_dputstr(2, command->command);
    my_dputstr(2, ": Command not found.\n");
    return 1;
}

static bool is_crash(int status)
{
    if (WIFSIGNALED(status)) {
        return WTERMSIG(status) == SIGSEGV;
    }
    return false;
}

int error_wait(const pid_t status, shell_t *shell,
    command_t *command, int new_fd)
{
    int exit_status = WEXITSTATUS(status);

    if (command->flag != NULL)
        if (my_strcmp(command->flag, "<<") == 0)
            return new_fd;
    shell->exit = exit_status;
    if (is_crash(status)) {
        shell->exit = 84;
        if (my_dputstr(2, "Segmentation fault (core dumped)\n") <= 0)
            return EXIT_ERROR;
    }
    if (command->next != NULL)
        return execute_commands(shell, command->next, new_fd);
    close(new_fd);
    return 0;
}

int execute_commands(shell_t *shell, command_t *command, int prev_fd)
{
    if (command->flag == NULL)
        return pipe_command(shell, command, prev_fd);
    if (my_strcmp(command->flag, ">") == 0)
        return redirect_to_file(shell, command, prev_fd);
    if (my_strcmp(command->flag, ">>") == 0)
        return redirect_to_file_and_append(shell, command, prev_fd);
    if (my_strcmp(command->flag, "<") == 0)
        return send_file_to_exec(shell, command, prev_fd);
    if (my_strcmp(command->flag, "<<") == 0)
        return read_to_exec(shell, command, prev_fd);
    return pipe_command(shell, command, prev_fd);
}

int default_command(shell_t *shell, command_t *command)
{
    return execute_commands(shell, command, -1);
}
