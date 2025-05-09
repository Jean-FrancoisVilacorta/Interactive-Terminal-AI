/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** get_files
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "my_getline.h"

int is_dir(const char *path)
{
    struct stat info;

    if (stat(path, &info) != 0) {
        return 0;
    }
    return S_ISDIR(info.st_mode);
}

static struct autoc_h *add_back(char **src, char *path, size_t len)
{
    char *new = malloc(sizeof(char) * (len + 2));

    if (new == NULL) {
        free(path);
        return NULL;
    }
    for (size_t i = 0; path[i] != '\0'; i++)
        new[i] = path[i];
    new[len] = '/';
    new[len + 1] = '\0';
    free(*src);
    free(path);
    *src = new;
    return NULL;
}

static void copy_content_from_x(char *src, size_t x, char *cpy)
{
    for (size_t i = 0; src[x] != '\0'; i++) {
        cpy[i] = src[x];
        cpy[i + 1] = '\0';
        x++;
    }
}

static struct autoc_h *manager_path_src(char **src, char *path, int last_back)
{
    char *new = NULL;
    char temp_path[last_back + 2];

    if (last_back == -1) {
        new = strdup(".");
        return get_files(new, path, src);
    }
    snprintf(temp_path, last_back + 2, "%s", path);
    if (is_dir(temp_path)) {
        new = strdup(path);
        copy_content_from_x(path, last_back + 1, new);
        path[last_back + 1] = '\0';
        return get_files(path, new, src);
    }
    return NULL;
}

static struct autoc_h *manager_src(char **src, char *path)
{
    int last_back = -1;

    for (size_t i = 0; path[i] != '\0'; i++) {
        if (path[i] == '/')
            last_back = i;
    }
    return manager_path_src(src, path, last_back);
}

static bool is_nothing(char *src)
{
    if (src == NULL)
        return true;
    if (src[0] == '\0') {
        return true;
    }
    return false;
}

struct autoc_h *manager_get_file(char **src)
{
    char *path = NULL;
    size_t len = 0;

    if (is_nothing(*src)) {
        path = strdup(".");
        if (path == NULL)
            return false;
        return get_files(path, NULL, src);
    }
    path = strdup(*src);
    if (path == NULL)
        return NULL;
    if (is_dir(path)) {
        len = strlen(path);
        if (path[len - 1] != '/')
            return add_back(src, path, len);
        return get_files(path, NULL, src);
    }
    return manager_src(src, path);
}
