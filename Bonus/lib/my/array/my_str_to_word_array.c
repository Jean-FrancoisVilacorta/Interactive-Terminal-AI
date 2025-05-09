/*
** EPITECH PROJECT, 2025
** count_word
** File description:
** str_to_word_aray
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

static int is_delim(char c, const char *delim)
{
    for (size_t i = 0; delim[i]; i++){
        if (c == delim[i])
            return SUCCESS;
    }
    return FAIL;
}

static int end_word(const char *str, int index, const char *delim)
{
    while (str[index] && is_delim(str[index], delim) == FAIL)
        index++;
    return index;
}

static int count_nb_word(const char *str, const char *delim)
{
    int index = 0;
    int nb_words = 0;

    if (!str)
        return 0;
    while (str[index]){
        if (is_delim(str[index], delim) == FAIL){
            nb_words++;
            index = end_word(str, index, delim);
            continue;
        }
        index++;
    }
    return nb_words;
}

static char *get_word(const char *str, const int begin,
    const char *delim)
{
    int len = end_word(str, begin, delim) - begin;
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word)
        return NULL;
    for (int i = 0; str[begin + i] && i < len; i++){
        word[i] = str[begin + i];
    }
    word[len] = '\0';
    return word;
}

char **my_str_to_word_arr(const char *str, const char *delim)
{
    int len = count_nb_word(str, delim);
    char **arr = malloc(sizeof(char *) * (len + 1));
    int index_arr = 0;

    if (!arr)
        return NULL;
    for (int i = 0; str[i] && index_arr < len; i++){
        if (is_delim(str[i], delim) == FAIL){
            arr[index_arr] = get_word(str, i, delim);
            index_arr++;
            i = end_word(str, i, delim) - 1;
        }
    }
    arr[index_arr] = NULL;
    return arr;
}

int len_word_arr(char **arr)
{
    int nb_word = 0;

    if (!arr)
        return -1;
    while (arr[nb_word])
        nb_word++;
    return nb_word;
}

char **cp_word_arr(char **origin)
{
    char **new = NULL;

    if (!origin)
        return new;
    new = malloc(sizeof(char *) * (len_word_arr(origin) + 1));
    if (!new)
        return NULL;
    for (int i = 0; origin[i]; i++){
        new[i] = malloc(sizeof(char) * (my_strlen(origin[i]) + 1));
        if (!new[i])
            return NULL;
        new[i][0] = '\0';
        my_strcpy(new[i], origin[i]);
    }
    new[len_word_arr(origin)] = NULL;
    return new;
}

void free_word_arr(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i] != NULL; i++){
        free(arr[i]);
    }
    free(arr);
}
