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
#include "lib.h"
#include "my_getline.h"

char *get_end(char *str)
{
    char *ret = NULL;
    int len = strlen(str);
    int x = 0;

    if (str == NULL || str[0] == '\0')
        return NULL;
    while (len != 0 && str[len] != '/' && str[len] != ' ') {
        len--;
        x++;
    }
    ret = malloc(sizeof(char) * (x + 1));
    if (str[len] == '/' || str[len] == ' ')
        len++;
    ret[0] = '\0';
    for (size_t i = 0; str[len] != '\0'; i++) {
        ret[i] = str[len];
        ret[i + 1] = '\0';
        len++;
    }
    return ret;
}

void count_autocomplete(struct line_h *data, size_t lines)
{
    struct autoc_h *file = data->autocomplete;
    size_t max_height = get_height() - lines;
    int max_size = get_max_size(data->autocomplete, 0) + 1;
    size_t how_many_str = (size_t)(data->len / max_size);

    for (size_t i = 0; i != max_height; i++) {
        for (size_t a = 0; a != how_many_str && file == NULL; a++)
            file = file->next;
        if (file == NULL) {
            data->auto_lines = i + 1;
            return;
        }
    }
}

static size_t count_str(char *str, struct line_h *data)
{
    size_t len = my_strlen(data->usr) + 8;
    size_t lines = 1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (data->len == len) {
            len = 0;
            lines++;
        }
        len++;
    }
    return lines;
}

void autocomplete_lines(struct line_h *data, struct history_t *buff)
{
    size_t lines = 0;

    if (buff->temp != NULL) {
        count_str(buff->temp, data);
        return;
    }
    if (buff->str != NULL)
        lines = count_str(buff->str, data);
    if (data->autocomplete != NULL) {
        count_autocomplete(data, lines);
    } else
        data->auto_lines = 0;
}

struct autoc_h *modify_auto(struct autoc_h *files, char *str)
{
    struct autoc_h *new = NULL;

    if (files == NULL)
        return NULL;
    if (my_compare_start(str, files->str) == true) {
        new = files;
        new->next = modify_auto(files->next, str);
        return new;
    }
    new = modify_auto(files->next, str);
    free(files->str);
    free(files);
    return new;
}
