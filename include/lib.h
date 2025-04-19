/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** lib
*/

#include <stdbool.h>
#include <stddef.h>

#ifndef INCLUDED_LIB_H
    #define INCLUDED_LIB_H

typedef struct cut_str_s {
    bool separor;
    bool ignore;
    size_t ignore_i;
    size_t i;
}cut_str_t;

int my_strlen(char const *str);
int my_strstrlen(char const *const *strstr);
char **my_str_to_word_array(char const *str, char const *separators);
int my_strcmp(const char *str1, const char *str2);
int my_strncmp(const char *str1, const char *str2, int const n);
int my_dputstr(int const nb, char const *str);
char *my_strcpy(char const *str);
char *my_skip_strcpy(char const *str, int const skip);
char **my_strstrcpy(char const *const *strstr);
char *my_realloc(char *str, size_t size);
char *my_getline(void);
char *my_str_cmb(const char *str1, const char *str2);

#endif
