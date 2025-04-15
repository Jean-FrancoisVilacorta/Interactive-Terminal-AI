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

static void print_red(const char *str)
{
    write(1, "\033[31m", 5);
    while (*str) {
        write(1, str, 1);
        str++;
    }
    write(1, "\033[0m", 4);
}

static void print_message(char **arr, int x, int *i)
{
    if (*i != x - 1) {
        my_dputstr(1, arr[*i]);
        my_dputstr(1, " ");
    } else {
        print_red(arr[*i]);
        my_dputstr(1, " ");
        if (arr[*i + 1] != NULL) {
            (*i)++;
            print_red(arr[*i]);
            my_dputstr(1, " ");
        }
    }
}

static void print_error(char **arr, int x)
{
    if (x == 0)
        x = 1;
    for (int i = 0; arr[i] != NULL; i++) {
        print_message(arr, x, &i);
    }
    my_dputstr(1, "\n");
}

static bool correct_format_redir(char **arr, int i,
    bool separators, bool pipes)
{
    if (separators || pipes) {
            print_error(arr, i);
            return false;
        }
        pipes = true;
    return correct_format(arr, i + 1, separators, pipes);
}

bool correct_format(char **arr, int i, bool separators, bool pipes)
{
    if (arr[i] == NULL)
        return true;
    if (search_dividers(arr[i])) {
        if (separators || pipes) {
            print_error(arr, i);
            return false;
        }
        separators = true;
    } else if (search_redir(arr[i])) {
        return correct_format_redir(arr, i, separators, pipes);
    } else {
        pipes = false;
        separators = false;
    }
    return correct_format(arr, i + 1, separators, pipes);
}
