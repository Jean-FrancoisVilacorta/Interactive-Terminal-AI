/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** is an alias
*/

#include "shell.h"
#include <stdio.h>

alias_t **get_list_alias(void)
{
    static alias_t *list = NULL;

    return &list;
}

char *is_an_alias(char *command)
{
    alias_t **list = get_list_alias();
    alias_t *current = (*list);

    while (current) {
        if (!strcmp(current->shortcut, command))
            return clean_str(clean_str(current->command, '('), ')');
        current = current->next;
    }
    return command;
}
