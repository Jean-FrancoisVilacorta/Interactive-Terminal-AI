/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** globbings.c
*/

#include "shell.h"
#include <glob.h>
#include <stdio.h>

static bool is_globbing(const char *arg)
{
    return (strchr(arg, '*') || strchr(arg, '[') || strchr(arg, '?'));
}

static char **get_new_cmds(glob_t globbing, int *size)
{
    char **new_cmds = NULL;

    for (size_t i = 0; i < globbing.gl_pathc; ++i) {
        new_cmds = realloc(new_cmds, sizeof(char *) * ((*size) + 2));
        if (new_cmds == NULL)
            return NULL;
        new_cmds[*size] = strdup(globbing.gl_pathv[i]);
        if (new_cmds[*size] == NULL)
            return NULL;
        (*size)++;
    }
    globfree(&globbing);
    return new_cmds;
}

static char **check_globbing(char **cmds, int *size, char **new_cmds, int i)
{
    glob_t globbing;

    if (is_globbing(cmds[i]) && glob(cmds[i], 0, NULL, &globbing) == 0) {
        new_cmds = get_new_cmds(globbing, size);
        if (new_cmds == NULL)
            return NULL;
    } else {
        new_cmds = realloc(new_cmds, sizeof(char *) * (*size + 2));
        if (new_cmds == NULL)
            return NULL;
        new_cmds[*size] = strdup(cmds[i]);
        if (new_cmds[*size] == NULL)
            return NULL;
        (*size)++;
    }
    new_cmds[*size] = NULL;
    return new_cmds;
}

char **find_globbings(char **cmds)
{
    char **new_cmds = NULL;
    int size = 0;

    for (size_t i = 0; cmds[i] != NULL; ++i) {
        new_cmds = check_globbing(cmds, &size, new_cmds, i);
        if (new_cmds == NULL)
            return NULL;
    }
    return new_cmds;
}
