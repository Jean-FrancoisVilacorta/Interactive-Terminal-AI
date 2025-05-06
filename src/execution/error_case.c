/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** error case
*/

#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>

bool pipe_is_alone(char **all_commands)
{
    char *temp = NULL;

    for (size_t i = 0; all_commands[i]; i++) {
        temp = strdup(all_commands[i]);
        temp = clean_str(clean_str(temp, ' '), '\t');
        if (!my_strcmp(temp, "|"))
            return true;
    }
    return false;
}

int is_command_valid(char **all_commands)
{
    if (!all_commands || !all_commands[0]){
        my_dprintf(STDERR_FD, "failed to get all_command\n");
        return FAIL;
    }
    if (pipe_is_alone(all_commands)) {
        my_dprintf(STDERR_FD, "Invalid null command.\n");
        return 1;
    }
    return EXIT_SUCCESS;
}
