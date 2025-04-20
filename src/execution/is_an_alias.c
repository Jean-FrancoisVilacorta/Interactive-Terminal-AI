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

alias_t *insertion_sort_alias(alias_t *current, alias_t *sorted)
{
    alias_t *temp = NULL;

    if (!sorted || my_strcmp(sorted->shortcut, current->shortcut) >= 0) {
        current->next = sorted;
        sorted = current;
    } else {
        temp = sorted;
        while (temp->next &&
        my_strcmp(temp->shortcut, current->shortcut) < 0) {
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
    return sorted;
}

void sort_list_alias(alias_t **list)
{
    alias_t *current = (*list);
    alias_t *sorted = NULL;
    alias_t *next = NULL;

    while (current) {
        next = current->next;
        sorted = insertion_sort_alias(current, sorted);
        current = next;
    }
    (*list) = sorted;
}

char *is_an_alias(char *command)
{
    alias_t **list = get_list_alias();
    alias_t *current = (*list);

    sort_list_alias(list);
    while (current) {
        if (!strcmp(current->shortcut, command))
            return clean_str(clean_str(current->command, '('), ')');
        current = current->next;
    }
    return command;
}
