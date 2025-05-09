/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** search_files
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "my_getline.h"

static int file_type2(char *file, struct stat *st)
{
    if (S_ISDIR(st->st_mode)) {
        free(file);
        return F_DIR;
    }
    free(file);
    return REGULAR_FILE;
}

static int file_type(char *path, char *str)
{
    struct stat st;
    char *file = my_str_cmb(path, str);

    if (file == NULL)
        return 0;
    if (stat(file, &st) != 0) {
        free(file);
        return REGULAR_FILE;
    }
    if (S_ISREG(st.st_mode)) {
        if (access(file, X_OK) == 0) {
            free(file);
            return EXEC;
        }
        free(file);
        return REGULAR_FILE;
    }
    return file_type2(file, &st);
}

bool my_compare_start(char *cmp, char *cmp2)
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
        if (file[0] == '.')
            return true;
        return false;
    }
    if (my_compare_start(ignore, file))
        return false;
    return true;
}

static struct autoc_h *verify_exit(struct autoc_h *files,
    char **src, char *path)
{
    char *temp_path = NULL;
    char *temp = NULL;

    temp_path = my_str_cmb(path, files->str);
    if (temp_path == NULL)
        return files;
    if (is_dir(temp_path)) {
        temp = my_str_cmb(files->str, "/");
        free(files->str);
        files->str = temp;
    }
    free(temp_path);
    free(*src);
    *src = files->str;
    free(files);
    free(path);
    return NULL;
}

static struct autoc_h *get_file_2(struct autoc_h *files, char **src,
    char *path, char *file)
{
    free(file);
    if (files == NULL) {
        free(path);
        return NULL;
    }
    if (files->next != NULL) {
        free(path);
        return files;
    }
    return verify_exit(files, src, path);
}

static struct autoc_h *read_files2(DIR *dir, data_t *data,
    struct autoc_h *files, struct autoc_h *new)
{
    if (files == NULL) {
        new->next = read_files(dir, data, new);
        return new;
    }
    new->before = files;
    new->next = read_files(dir, data, new);
    return new;
}

struct autoc_h *read_files(DIR *dir, data_t *data,
    struct autoc_h *files)
{
    struct dirent *entry;
    struct autoc_h *new;

    entry = readdir(dir);
    if (entry == NULL)
        return NULL;
    if (ignore_get_file(entry->d_name, data->file))
        return read_files(dir, data, files);
    new = malloc(sizeof(struct autoc_h));
    if (new == NULL)
        return NULL;
    new->str = strdup(entry->d_name);
    new->type = file_type(data->path, new->str);
    new->next = NULL;
    if (new->str == NULL) {
        free(new);
        return NULL;
    }
    return read_files2(dir, data, files, new);
}

struct autoc_h *get_files(char *path, char *file, char **src)
{
    DIR *dir = opendir(path);
    struct data_h data = {file, path};
    struct autoc_h *files = NULL;

    if (!dir)
        return NULL;
    files = read_files(dir, &data, NULL);
    closedir(dir);
    return get_file_2(files, src, path, file);
}
