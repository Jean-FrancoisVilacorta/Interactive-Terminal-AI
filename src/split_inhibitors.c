/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** my_str_to_word_array
*/

#include "lib.h"
#include <stdlib.h>
#include <stddef.h>

static const char *ignore = "\"\'";
static const char *endignore = "\"\'";
static const char replace = '\n';

static bool search_separator(char const letter, char const *separators)
{
    for (size_t i = 0; separators[i] != '\0'; i++) {
        if (separators[i] == letter)
            return true;
    }
    return false;
}

static int search_ignore(char const letter, char const *separators)
{
    for (size_t i = 0; separators[i] != '\0'; i++) {
        if (separators[i] == letter)
            return i;
    }
    return -1;
}

static void analyze_letter(char const letter, char *short_str,
    char const *separators, cut_str_t *data)
{
    if (search_separator(letter, separators) == true) {
        if (data->separor == false) {
            data->separor = true;
            short_str[data->i] = replace;
            data->i++;
        }
    } else {
        data->separor = false;
        short_str[data->i] = letter;
        data->i++;
    }
}

static void analyze_ignore(char const letter, char *short_str,
    char const *separators, cut_str_t *data)
{
    if (data->ignore == false) {
        if (search_separator(letter, ignore) == true) {
            data->ignore = true;
            data->ignore_i = search_ignore(letter, ignore);
            short_str[data->i] = letter;
            data->i++;
            return;
        }
        analyze_letter(letter, short_str, separators, data);
    } else {
        short_str[data->i] = letter;
        data->i++;
        if (letter == endignore[data->ignore_i]) {
            data->ignore = false;
            data->ignore_i = 0;
            return;
        }
    }
}

static void cut_str(char const *str, char *short_str, char const *separators)
{
    cut_str_t data = {false, false, 0, 0};

    for (size_t x = 0; str[x] != '\0'; x++) {
        analyze_ignore(str[x], short_str, separators, &data);
    }
    short_str[data.i] = '\0';
}

static size_t how_many_lines(char const *str)
{
    int lines = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == replace)
            lines++;
    }
    return lines;
}

static char *copy_from_x(char const *str, size_t x, size_t len)
{
    int i = 0;
    int a = 0;
    size_t b = 0;
    char *copy = NULL;

    copy = malloc(sizeof(char) * (len + 2 - i - a));
    while (str[x + i] != replace && str[x + i] != '\0') {
        copy[b] = str[x + i];
        b++;
        x++;
    }
    copy[b - a] = '\0';
    return copy;
}

static char **create_str_str(char *short_str)
{
    size_t x = 0;
    size_t a = 0;
    size_t len = how_many_lines(short_str);
    char **array = malloc(sizeof(char *) * (len + 2));

    if (short_str[0] == '\n')
        x = 1;
    len = 0;
    for (size_t i = x; short_str[i] != '\0'; i++) {
        if (short_str[i] == '\n' || short_str[i + 1] == '\0') {
            array[a] = copy_from_x(short_str, x, len);
            x = i + 1;
            a++;
            len = 0;
        } else
            len++;
    }
    array[a] = NULL;
    free(short_str);
    return array;
}

char **split_command_line(char const *str, char const *separators)
{
    int len = my_strlen(str);
    char *short_str = NULL;

    if (len == -1 || separators == NULL)
        return NULL;
    short_str = malloc(sizeof(char *) * (len + 1));
    if (short_str == NULL)
        return NULL;
    cut_str(str, short_str, separators);
    return create_str_str(short_str);
}
