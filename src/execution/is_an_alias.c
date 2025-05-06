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

static alias_t *insertion_sort_alias(alias_t *current, alias_t *sorted)
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

static void sort_list_alias(alias_t **list)
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

void free_list_alias(void)
{
    alias_t **list = get_list_alias();
    alias_t *current = (*list);
    alias_t *before = NULL;

    while (current) {
        before = current->next;
        free(current);
        current = before;
    }
}

char *is_an_alias(char *command)
{
    alias_t **list = get_list_alias();
    alias_t *current = (*list);
    char *cmd = NULL;
    size_t len = 0;
    char *concat = NULL;

    sort_list_alias(list);
    while (current) {
        len = strlen(current->shortcut);
        if (!strncmp(current->shortcut, command, len)) {
            concat = skip_char_begin(command, len);
            cmd = malloc(strlen(concat) + strlen(current->command));
            strcpy(cmd, current->command);
            strcat(cmd, concat);
            return clean_str(clean_str(cmd, '('), ')');
        }
        current = current->next;
    }
    return command;
}
