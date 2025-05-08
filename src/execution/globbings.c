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

static char **get_new_cmds(glob_t globbing, int *size, char **new_cmds)
{
    char **tmp = NULL;

    for (size_t i = 0; i < globbing.gl_pathc; ++i) {
        tmp = realloc(new_cmds, sizeof(char *) * ((*size) + 2));
        if (!tmp)
            return NULL;
        new_cmds = tmp;
        new_cmds[*size] = strdup(globbing.gl_pathv[i]);
        if (!new_cmds[*size])
            return NULL;
        (*size)++;
        new_cmds[*size] = NULL;
    }
    globfree(&globbing);
    return new_cmds;
}

static char **not_globbing(char **cmds, int i, int *size, char **new_cmds)
{
    char **tmp = realloc(new_cmds, sizeof(char *) * (*size + 2));

    if (!tmp)
        return NULL;
    new_cmds = tmp;
    new_cmds[*size] = strdup(cmds[i]);
    if (!new_cmds[*size])
        return NULL;
    (*size)++;
    new_cmds[*size] = NULL;
    return new_cmds;
}

static char **check_globbing(char **cmds, int *size, char **new_cmds, int i)
{
    glob_t globbing;
    int if_match = 0;

    if (is_globbing(cmds[i])) {
        if_match = glob(cmds[i], 0, NULL, &globbing);
        if (if_match == GLOB_NOMATCH) {
            dprintf(STDERR_FILENO,
                "\"%s\": No such file or directory\n", cmds[i]);
            return NULL;
        }
        return get_new_cmds(globbing, size, new_cmds);
    } else
        return not_globbing(cmds, i, size, new_cmds);
    return NULL;
}

char **find_globbings(char **cmds)
{
    int size = 0;
    char **new_cmds = malloc(sizeof(char *));

    if (!new_cmds)
        return NULL;
    for (size_t i = 0; cmds[i] != NULL; ++i) {
        new_cmds = check_globbing(cmds, &size, new_cmds, i);
        if (!new_cmds)
            return NULL;
    }
    new_cmds[size] = NULL;
    return new_cmds;
}
