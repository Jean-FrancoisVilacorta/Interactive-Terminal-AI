/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** search_files
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "lib.h"
#include "my_getline.h"

static bool my_compare_start(char *cmp, char *cmp2)
{
    if (cmp == NULL || cmp2 == NULL)
        return false;
    for (size_t i = 0; cmp[i] != '\0'; i++) {
        if (cmp2[i] != cmp[i])
            return false;
    }
    return true;
}

static bool ignore_get_file(char *file, char *ignore)
{
    if (ignore == NULL) {
        if (strcmp(file, ".") == 0 || strcmp(file, "..") == 0) {
            return true;
        }
        return false;
    }
    if (my_compare_start(ignore, file))
        return false;
    return true;
}

static char **verify_exit(char **files, char **src, char *path)
{
    char *temp_path = NULL;
    char *temp = NULL;

    temp_path = my_str_cmb(path, files[0]);
    if (temp_path == NULL)
        return files;
    if (is_dir(temp_path)) {
        temp = my_str_cmb(files[0], "/");
        free(files[0]);
        files[0] = temp;
    }
    free(temp_path);
    free(*src);
    *src = files[0];
    free(files);
    free(path);
    return NULL;
}

static char **get_file_2(char **files, char **src, char *path, char *file)
{
    free(file);
    if (files == NULL) {
        free(path);
        return NULL;
    }
    if (files[1] != NULL) {
        free(path);
        return files;
    }
    return verify_exit(files, src, path);
}

static char **verify_if_add(char **files, int count)
{
    if (files == NULL)
        return NULL;
    files = realloc(files, sizeof(char *) * (count + 1));
    if (files == NULL)
        return NULL;
    files[count] = NULL;
    return files;
}

char **get_files(char *path, char *file, char **src)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    char **files = NULL;
    int count = 0;

    if (!dir)
        return NULL;
    entry = readdir(dir);
    while (entry != NULL) {
        if (ignore_get_file(entry->d_name, file))
            continue;
        files = realloc(files, sizeof(char *) * (count + 1));
        files[count] = strdup(entry->d_name);
        count++;
        entry = readdir(dir);
    }
    closedir(dir);
    files = verify_if_add(files, count);
    return get_file_2(files, src, path, file);
}
