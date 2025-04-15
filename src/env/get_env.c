/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** get_env
*/

#include <stddef.h>
#include "lib.h"

char *get_env_data(char const *src, char const *const *env)
{
    int len = my_strlen(src);

    if (env == NULL && src == NULL)
        return NULL;
    for (size_t i = 0; env[i] != NULL; i++) {
        if (my_strncmp(src, env[i], len) == 0)
            return my_skip_strcpy(env[i], len);
    }
    return NULL;
}

static int my_strncmp_env(const char *str1, const char *str2, int const n)
{
    char c1 = '\0';
    char c2 = '\0';
    int x = 0;

    while (str1[x] != '\0' && str2[x] != '\0' && x != n) {
        c1 = str1[x];
        c2 = str2[x];
        if (str1[x] == '=')
            return 1;
        if (c1 != c2) {
            return (unsigned char)c1 - (unsigned char)c2;
        }
        x++;
    }
    if (str2[x] != '=')
        return 1;
    return 0;
}

int get_env_x(char const *src, char const *const *env)
{
    int len = my_strlen(src);

    if (env == NULL && src == NULL)
        return -2;
    for (size_t i = 0; env[i] != NULL; i++) {
        if (my_strncmp_env(src, env[i], len) == 0)
            return i;
    }
    return -1;
}

char *get_env(char const *src, char const *const *env)
{
    int len = my_strlen(src);

    if (env == NULL && src == NULL)
        return NULL;
    for (size_t i = 0; env[i] != NULL; i++) {
        if (my_strncmp(src, env[i], len) == 0)
            return my_strcpy(env[i]);
    }
    return NULL;
}
