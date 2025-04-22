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

void count_autocomplete(struct line_h *data, size_t lines)
{
    struct autoc_h *file = data->autocomplete;
    size_t max_height = get_height() - lines;
    int max_size = get_max_size(data->autocomplete, 0) + 1;
    size_t how_many_str = (size_t)(data->len / max_size);

    for (size_t i = 0; i != max_height; i++) {
        for (size_t a = 0; a != how_many_str; a++) {
            if (file->next == NULL) {
                data->auto_lines = i + 1;
                return;
            }
            file = file->next;
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
