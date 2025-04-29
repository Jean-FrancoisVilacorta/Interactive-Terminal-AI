/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** main loop
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void display_prompt(void)
{
    if (isatty(STDIN_FILENO))
        my_dprintf(STDOUT_FD, "$> ");
}

static int handle_command(char *command, char ***env)
{
    int status = 0;

    if (!my_strcmp(command, ""))
        return status;
    if (!my_strncmp(command, "exit", 4)) {
        my_dprintf(STDOUT_FD, "exit\n");
        return -1;
    }
    status = exec_all_commands(command, env);
    return status;
}

int shell_loop(char ***env, int is_tty)
{
    char *command = NULL;
    size_t n = 0;
    int status = 0;
    job_t **jobs = get_jobs_list();

    while (1) {
        display_prompt();
        if (getline(&command, &n, stdin) == -1)
            break;
        command[my_strlen(command) - 1] = '\0';
        update_job_status(jobs);
        status = handle_command(command, env);
        if (status == -1 || (!is_tty && !my_strcmp(command, "")))
            break;
        free(command);
        command = NULL;
    }
    free(command);
    return status;
}
