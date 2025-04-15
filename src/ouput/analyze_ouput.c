/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** analyze_ouput
*/

#include <stdlib.h>
#include "shell.h"
#include "lib.h"

static char const redirects[] = {'\t', ' ', '\n', '\0'};

static int execute_command(shell_t *shell, command_t *command)
{
    for (size_t i = 0; flag[i].func != NULL; i++) {
        if (my_strcmp(command->command, flag[i].command) == 0)
            return flag[i].func(shell, command);
    }
    return default_command(shell, command);
}

static int read_commands(shell_t *shell, command_t *commands)
{
    if (commands == NULL)
        return SUCCESS;
    if (execute_command(shell, commands) == EXIT_ERROR) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    return SUCCESS;
}

static int read_divisers(shell_t *shell, dividers_t *div)
{
    if (div == NULL) {
        free_dividers(shell->dividers);
        shell->dividers = NULL;
        return SUCCESS;
    }
    if (read_commands(shell, div->commands) == EXIT_ERROR) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    return read_divisers(shell, div->next);
}

static bool find_text(char b)
{
    for (size_t i = 0; redirects[i]; i++) {
        if (redirects[i] == b)
            return false;
    }
    return true;
}

static bool case_of_error(char *string)
{
    int x = 0;

    if (string == NULL)
        return NULL;
    while (string[x] != '\0') {
        if (find_text(string[x]))
            return false;
        x++;
    }
    return true;
}

int analyze_ouput(shell_t *shell, char *ouput)
{
    char a = 0;

    if (case_of_error(ouput)) {
        free(ouput);
        return 2;
    }
    shell->dividers = struct_commands(ouput, &a);
    free(ouput);
    if (a == 2)
        return SUCCESS;
    if (shell->dividers == NULL) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    return read_divisers(shell, shell->dividers);
}
