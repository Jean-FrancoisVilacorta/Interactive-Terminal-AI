/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** autocomplete
*/

#include "my_getline.h"
#include <stdio.h>
#include <string.h>

static const char stop_arg[] = {' ', '\t', '\0',
    ';', '&', '>', '<', '\0'};

void free_auto(struct autoc_h *file)
{
    if (file == NULL)
        return;
    if (file->str != NULL)
        free(file->str);
    free_auto(file->next);
    free(file);
}

bool stop(char c)
{
    for (size_t i = 0; stop_arg[i] != '\0'; i++) {
        if (stop_arg[i] == c)
            return true;
    }
    return false;
}

static char *get_last_path2(char *str, int len, int x)
{
    char *new = malloc(sizeof(char) * (len + 2));

    if (new == NULL)
        return NULL;
    for (size_t i = 0; str[x] != '\0'; i++) {
        if (stop(str[x])) {
            new[i] = '\0';
            break;
        }
        new[i] = str[x];
        new[i + 1] = '\0';
        x++;
    }
    return new;
}

static char *get_last_path(char *str)
{
    int len = 0;
    int x = 0;

    if (str == NULL)
        return strdup("./");
    if (str[0] == '\0')
        return strdup("./");
    x = strlen(str) - 1;
    while (x != 0) {
        len++;
        if (stop(str[x]))
            break;
        x--;
    }
    if (stop(str[x]))
        x++;
    if (str[x] == '\0')
        return strdup("./");
    return get_last_path2(str, len, x);
}

void add_change(struct history_t *buff, char *path)
{
    size_t len = 0;
    char *temp = NULL;

    if (buff->str == NULL) {
        buff->str = my_str_cmb("./", path);
        return;
    }
    len = strlen(buff->str);
    while (len != 0) {
        if (stop(buff->str[len]) || buff->str[len] == '/')
            break;
        len--;
    }
    if (len == 0)
        buff->str[len] = '\0';
    else
        buff->str[len + 1] = '\0';
    temp = my_str_cmb(buff->str, path);
    free(buff->str);
    buff->str = temp;
}

static bool autocomplete2(struct line_h *data, struct history_t *buff,
    struct history_t **history)
{
    struct autoc_h *new_list = NULL;
    char *path = get_last_path(buff->str);
    char *cmp = strdup(path);

    if (buff->temp != NULL)
        (*history) = change_the_buff(buff, *history);
    new_list = manager_get_file(&path);
    if (strcmp(cmp, path) != 0) {
        add_change(buff, path);
    }
    free(path);
    free(cmp);
    if (data->autocomplete != NULL)
        free_auto(data->autocomplete);
    data->autocomplete = new_list;
    return true;
}

bool autocomplete(struct line_h *data, struct history_t *buff,
    struct history_t **history)
{
    if (data->autocomplete != NULL)
        if (data->autocomplete->next != NULL)
            return change_column(data);
    return autocomplete2(data, buff, history);
}
