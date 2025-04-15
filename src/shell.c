/*
** EPITECH PROJECT, 2025
** Minishell
** File description:
** shell
*/

#include "lib.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int exit_shell(shell_t *shell, command_t *command)
{
    if (command == NULL)
        return EXIT_ERROR;
    free_shell(shell);
    if (my_dputstr(1, "exit\n") <= 0)
            return EXIT_ERROR;
    exit(0);
}

static int fast_exit(int const exit_status)
{
    if (isatty(0) == 1) {
        if (my_dputstr(1, "exit\n") <= 0)
            return EXIT_ERROR;
    }
    return (exit_status);
}

static char *ask_for_ouput(shell_t *shell)
{
    char *ouput = NULL;

    if (isatty(0) == 1) {
        if (my_dputstr(1, "$> ") <= 0)
            return NULL;
    }
    ouput = my_getline();
    if (ouput == NULL) {
        free_shell(shell);
        return NULL;
    }
    return ouput;
}

static int run_shell(shell_t *shell)
{
    bool run = true;
    char *ouput = NULL;
    int exit_status = 0;

    while (run == true) {
        ouput = ask_for_ouput(shell);
        if (ouput == NULL) {
            return fast_exit(exit_status);
        }
        if (analyze_ouput(shell, ouput) == EXIT_ERROR)
            return EXIT_ERROR;
        exit_status = shell->exit;
    }
    free_shell(shell);
    return EXIT_SUCCESS;
}

int prepare_shell(char const *const *env)
{
    shell_t *shell = malloc(sizeof(shell_t) * 1);

    if (shell == NULL)
        return EXIT_ERROR;
    shell->env = my_strstrcpy(env);
    if (shell->env == NULL) {
        free_shell(shell);
        return EXIT_ERROR;
    }
    if (default_info(shell, env) == EXIT_ERROR)
        return EXIT_ERROR;
    return run_shell(shell);
}
