/*
** EPITECH PROJECT, 2025
** Minishell
** File description:
** shell
*/

#include "lib.h"
#include "shell.h"

int help(void)
{
    if (my_dputstr(1, "It's just a shell...\n") <= 0)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int main(int const ac, char const *const *av, char const *const *env)
{
    if (ac == 2) {
        if (my_strcmp(av[1], "-h") == 0 || my_strcmp(av[1], "-help") == 0)
            return help();
        else
            return EXIT_ERROR;
    }
    if (ac != 1)
        return EXIT_ERROR;
    return prepare_shell(env);
}
