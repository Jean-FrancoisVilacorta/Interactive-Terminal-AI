/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** struct_commands
*/

#include "lib.h"
#include "shell.h"
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static char const *const dividers[] = {";",
    "&&",
    NULL};

static char const *const redirects[] = {">",
    ">>", "<", "|", "<<", NULL};

bool search_dividers(char const *str)
{
    for (size_t i = 0; dividers[i] != NULL; i++) {
        if (my_strcmp(dividers[i], str) == 0)
            return true;
    }
    return false;
}

bool search_redir(char const *str)
{
    for (size_t i = 0; redirects[i] != NULL; i++) {
        if (my_strcmp(redirects[i], str) == 0)
            return true;
    }
    return false;
}

static size_t count_commands(char **arr, int i)
{
    size_t count = 0;

    while (arr[i] != NULL && search_redir(arr[i]) == false &&
        search_dividers(arr[i]) == false) {
        count++;
        i++;
    }
    return count;
}

static int its_the_end(char **arr, int i, command_t *command)
{
    if (arr[i] == NULL || search_dividers(arr[i]) == true) {
        command->next = NULL;
        command->flag = NULL;
        return i;
    }
    command->flag = arr[i];
    command->next = malloc(sizeof(command_t) * 1);
    if (command->next == NULL)
        return STOP_ERROR;
    command->next->before = command;
    return organize_command_struct(arr, i + 1, command->next);
}

int organize_command_struct(char **arr, int i, command_t *command)
{
    size_t nb_commands = count_commands(arr, i + 1);
    size_t a = 0;

    command->command = arr[i];
    i++;
    if (nb_commands == 0)
        command->ouput = NULL;
    else {
        command->ouput = malloc(sizeof(char *) * (nb_commands + 1));
        if (command->ouput == NULL)
            return STOP_ERROR;
        while (arr[i] != NULL && !search_redir(arr[i]) &&
            !search_dividers(arr[i])) {
            command->ouput[a] = arr[i];
            a++;
            i++;
        }
        command->ouput[a] = NULL;
    }
    return its_the_end(arr, i, command);
}

static int extract_command(char **arr, dividers_t *div,
    command_t *commands, int i)
{
    i = organize_command_struct(arr, i, commands);
    if (i == STOP_ERROR)
        return STOP_ERROR;
    div->commands = commands;
    return i;
}

static int organize_division(char **arr, dividers_t *div, int i)
{
    command_t *commands = malloc(sizeof(command_t) * 1);

    if (commands == NULL)
        return STOP_ERROR;
    i = extract_command(arr, div, commands, i);
    if (i == STOP_ERROR)
        return STOP_ERROR;
    div->flag = arr[i];
    if (arr[i] == NULL) {
        div->next = NULL;
        return SUCCESS;
    }
    div->next = malloc(sizeof(dividers_t) * 1);
    if (div->next == NULL)
        return STOP_ERROR;
    return organize_division(arr, div->next, i + 1);
}

dividers_t *struct_commands(char const *str, char *a)
{
    char **array = my_str_to_word_array(str, " \t");
    dividers_t *div = NULL;

    if (array == NULL)
        return NULL;
    if (!correct_format(array, 0, true, true)) {
        double_free(array);
        *a = 2;
        return NULL;
    }
    div = malloc(sizeof(command_t) * (1));
    organize_division(array, div, 0);
    free(array);
    return div;
}
