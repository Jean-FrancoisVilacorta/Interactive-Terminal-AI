/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** get env variable from command
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

static bool is_repeat_valid(char **commands)
{
    if (my_array_len(commands) < 3) {
        dprintf(2, "repeat: Too few arguments.\n");
        return false;
    }
    if (is_str_int(commands[1]) == FAIL) {
        dprintf(2, "repeat: Badly formed number.\n");
        return false;
    }
    return true;
}

static size_t keep_only_command_in_array(char **commands)
{
    delete_element_array(commands, 0);
    delete_element_array(commands, 0);
    return my_array_len(commands);
}

size_t get_full_len_command(char **commands)
{
    size_t len = 0;

    for (size_t i = 0; commands[i]; i++)
        len += strlen(commands[i]);
    return len;
}

static char *format_commands(size_t len, size_t array_len, char **commands)
{
    char *concat_command = malloc((len + 1 + array_len));

    if (!concat_command)
        return NULL;
    memset(concat_command, '\0', (len + 1 + array_len));
    for (size_t i = 0; commands[i]; i++) {
        strcat(concat_command, commands[i]);
        strcat(concat_command, " ");
    }
    return concat_command;
}

int builtin_repeat(char ***env, char **commands)
{
    int nb_loop = 0;
    size_t len = 0;
    char *concat_command = NULL;
    size_t array_len = 0;

    if (!is_repeat_valid(commands))
        return 1;
    nb_loop = atoi(commands[1]);
    if (nb_loop < 0)
        return 0;
    array_len = keep_only_command_in_array(commands);
    len = get_full_len_command(commands);
    concat_command = format_commands(len, array_len, commands);
    if (!concat_command)
        return 0;
    for (int i = 0; i < nb_loop; i++)
        exec_all_commands(concat_command, env);
    free(concat_command);
    return 0;
}
