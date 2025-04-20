/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** env builtin
*/

#include "shell.h"
#include <stdio.h>

static void delete_alias(alias_t **list, char *shortcut_to_delete)
{
    alias_t *current = (*list);
    alias_t *before = NULL;

    while (current) {
        if (!strcmp(current->shortcut, shortcut_to_delete) && before) {
            before->next = current->next;
            free(current);
            return;
        }
        if (!strcmp(current->shortcut, shortcut_to_delete) && !before) {
            before = (*list);
            (*list) = current->next;
            return;
        }
        before = current;
        current = current->next;
    }
}

int builtin_unalias(UNUSED char ***env, char **commands)
{
    alias_t **list = get_list_alias();
    size_t len = my_array_len(commands);

    if (len <= 1) {
        printf("unalias: Too few arguments.\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 1; i < len; i++)
        delete_alias(list, commands[i]);
    return 0;
}
