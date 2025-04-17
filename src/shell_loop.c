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

int shell_loop(char ***env, int is_tty)
{
    char *command = NULL;
    size_t n = 0;
    int exit_status = 0;

    while (OPEN){
        if (is_tty)
            my_dprintf(STDOUT_FD, "$> ");
        getline(&command, &n, stdin);
        command[my_strlen(command) - 1] = '\0';
        if (!my_strcmp(command, "exit") ||
            (!is_tty && !my_strcmp(command, ""))) {
            my_dprintf(STDOUT_FD, "exit\n");
            break;
        }
        if (my_strcmp(command, ""))
            exit_status = exec_all_commands(command, env);
        command = NULL;
    }
    free(command);
    return exit_status;
}
