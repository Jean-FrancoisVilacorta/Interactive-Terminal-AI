/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** env builtin
*/

#include "shell.h"
#include <stdio.h>

static alias_t *create_alias(char *shortcut, char *command)
{
    alias_t *nodes = malloc(sizeof(alias_t));

    if (!nodes)
        return NULL;
    nodes->shortcut = (shortcut != NULL) ? shortcut : NULL;
    nodes->command = (command != NULL) ? command : NULL;
    nodes->next = NULL;
    return nodes;
}

static void print_list_alias(alias_t **list)
{
    alias_t *current = (*list);

    while (current) {
        printf("%s\t %s\n", current->shortcut, current->command);
        current = current->next;
    }
}

static int check_alias_validity(char **commands)
{
    size_t len = my_array_len(commands);

    if (len == PRINT_ALIAS || len == INVALID_ALIAS)
        return len;
    return 0;
}

bool is_inquote(char *command)
{
    size_t len = strlen(command);

    command[strcspn(command, "'\n''\0''\t'' '")] = '\0';
    if (command[0] == '\'' && command[len - 1] == '\'')
        return true;
    if (command[0] == '"' && command[len - 1] == '"')
        return true;
    return false;
}

static char *enclose_str(char *str, char *addons)
{
    char *str_addons = malloc(strlen(str) + (strlen(addons) * 2) + 1);

    if (!str_addons)
        return NULL;
    strcpy(str_addons, addons);
    strcat(str_addons, str);
    strcat(str_addons, addons);
    return str_addons;
}

static char *get_alias_command(char **commands)
{
    char *str_command = commands[2];
    size_t len = 0;

    for (size_t i = 3; commands[i]; i++) {
        len = strlen(commands[i]);
        str_command = realloc(str_command, (len + 2));
        strcat(str_command, " ");
        strcat(str_command, commands[i]);
    }
    if (!is_inquote(str_command)) {
        str_command = enclose_str(str_command, "(");
        str_command[strlen(str_command) - 1] = ')';
    } else
        str_command = clean_str(str_command, '"');
    return (str_command) ? str_command : NULL;
}

int is_alias_invalid(alias_t **list, char **commands)
{
    int validy_code = check_alias_validity(commands);

    if (validy_code) {
        if (validy_code == INVALID_ALIAS) {
            return EXIT_FAILURE;
        }
        if (validy_code == PRINT_ALIAS) {
            print_list_alias(list);
            return EXIT_FAILURE;
        }
    }
    return SUCCESS;
}

void add_new_alias(alias_t **list, char *shortcut, char *command)
{
    alias_t *new_nodes = NULL;
    alias_t *current = (*list);

    while (current) {
        if (!strcmp(current->shortcut, shortcut)) {
            current->command = command;
            return;
        }
        current = current->next;
    }
    new_nodes = create_alias(shortcut, command);
    new_nodes->next = (*list);
    (*list) = new_nodes;
}

int builtin_alias(UNUSED char ***env, char **commands)
{
    alias_t **list = get_list_alias();
    char *command = NULL;
    char *shortcut = NULL;

    if (is_alias_invalid(list, commands))
        return SUCCESS;
    shortcut = (commands[1] != NULL) ? commands[1] : NULL;
    command = get_alias_command(commands);
    if (!(*list))
        (*list) = create_alias(shortcut, command);
    else
        add_new_alias(list, shortcut, command);
    return SUCCESS;
}
