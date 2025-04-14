/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** main
*/

#include "shell.h"
#include <unistd.h>

int main(int argc, UNUSED char **argv, char **env)
{
    char **env_cp = NULL;
    int exit_status = 0;

    if (argc != 1)
        return 84;
    env_cp = cp_word_arr(env);
    exit_status = shell_loop(&env_cp, isatty(STDIN_FILENO));
    free_word_arr(env_cp);
    return exit_status;
}
