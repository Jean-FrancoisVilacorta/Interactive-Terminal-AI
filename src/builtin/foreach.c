/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** get env variable from command
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

static bool is_valid_parenthesis(char **commands, size_t len)
{
    if (commands[2][0] == '(' &&
            commands[len - 1][strlen(commands[len - 1]) - 1] != ')') {
        dprintf(2, "Too many (\'s\n");
        return false;
    }
    if (commands[2][0] != '(' &&
            commands[len - 1][strlen(commands[len - 1]) - 1] == ')') {
        dprintf(2, "Too many )\'s\n");
        return false;
    }
    if (commands[2][0] != '(' && commands[len - 1][0] != ')') {
        dprintf(2, "foreach: Words not parenthesized.\n");
        return false;
    }
    return true;
}

static bool is_foreach_valid(char **commands)
{
    size_t len = my_array_len(commands);

    if (len < 3) {
        dprintf(2, "foreach: Too few arguments.\n");
        return false;
    }
    if (!is_alpha(commands[1][0])) {
        dprintf(2, "foreach: Variable name must begin with a letter.\n");
        return false;
    }
    if (!is_valid_parenthesis(commands, len))
        return false;
    return true;
}

foreach_t *create_each_nodes(char *commands)
{
    foreach_t *new_nodes = malloc(sizeof(foreach_t));

    if (!new_nodes)
        return NULL;
    new_nodes->next = NULL;
    new_nodes->command = (commands != NULL) ? strdup(commands) : NULL;
    return new_nodes;
}

void add_command_foreach(foreach_t **list, char *command)
{
    foreach_t *new_nodes = create_each_nodes(command);

    if (!(list))
        (*list) = new_nodes;
    else {
        new_nodes->next = (*list);
        (*list) = new_nodes;
    }
}

void print_each_command(foreach_t *list)
{
    foreach_t *current = (list);

    while (current) {
        printf("command [ %s ]\n", current->command);
        current = current->next;
    }
}

int builtin_foreach(char ***env, char **commands)
{
    size_t len = 0;
    char *line = NULL;
    foreach_t *list = NULL;

    if (!is_foreach_valid(commands))
        return 1;
    while (getline(&line, &len, stdin) != EOF) {
        line[strcspn(line, "\n \t")] = '\0';
        if (!strcmp(line, "end"))
            break;
        add_command_foreach(&list, line);
        print_each_command(list);
    }
    return 0;
}
