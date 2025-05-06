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

static int skip_parenthese(const char *str, int index)
{
    if (str[index] == '('){
        while (str[index] && str[index] != ')')
            index++;
    }
    return index;
}

static int end_word(const char *str, int index, const char *delim)
{
    while (str[index] && is_delim(str[index], delim) == FAIL){
        index = skip_parenthese(str, index);
        index++;
    }
    return index;
}

static int count_nb_word(const char *str, const char *delim)
{
    int index = 0;
    int nb_words = 0;

    if (!str)
        return 0;
    while (str[index]){
        index = skip_parenthese(str, index);
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

char **my_str_to_word_arr_ignore(const char *str,
    const char *delim)
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
