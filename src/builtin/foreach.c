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

static foreach_t *create_each_nodes(char *commands)
{
    foreach_t *new_nodes = malloc(sizeof(foreach_t));

    if (!new_nodes)
        return NULL;
    new_nodes->next = NULL;
    new_nodes->command = (commands != NULL) ? strdup(commands) : NULL;
    return new_nodes;
}

static void add_command_foreach(foreach_t **list, char *command)
{
    foreach_t *new_nodes = create_each_nodes(command);
    foreach_t *current = (*list);

    if (!current) {
        (*list) = new_nodes;
        return;
    }
    while (current) {
        if (!current->next) {
            current->next = new_nodes;
            return;
        }
        current = current->next;
    }
}

static char *replace_each_command(char *dictionary,
    char *list_cmd, char *command)
{
    char *value = strstr(command, "$");
    char *replace = NULL;
    size_t index = value - command;

    if (!value)
        return command;
    value++;
    if (strncmp(dictionary, value, strlen(dictionary)))
        return command;
    list_cmd = clean_str(clean_str(list_cmd, '('), ')');
    replace = malloc(index + strlen(list_cmd) + 1);
    if (!replace)
        return NULL;
    strncpy(replace, command, index);
    replace[index] = '\0';
    strcat(replace, list_cmd);
    return replace;
}

void exec_for_each(foreach_t *list, char **commands, char ***env)
{
    char *dictionary = commands[1];

    delete_element_array(commands, 0);
    delete_element_array(commands, 0);
    for (size_t i = 0; commands[i]; i++) {
        for (foreach_t *current = list; current; current = current->next) {
            exec_all_commands(
            replace_each_command(dictionary, commands[i], current->command)
                                , env);
        }
    }
}

void free_list_foreach(foreach_t **list)
{
    foreach_t *current = (*list);
    foreach_t *before = NULL;

    while (current) {
        before = current->next;
        free(current);
        current = before;
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
        line[strcspn(line, "\n")] = '\0';
        if (!strcmp(line, "end"))
            break;
        add_command_foreach(&list, line);
    }
    exec_for_each(list, commands, env);
    free_list_foreach(&list);
    return 0;
}
