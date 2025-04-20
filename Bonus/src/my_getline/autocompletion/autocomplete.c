/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** autocomplete
*/

#include "lib.h"
#include "my_getline.h"
#include <stdio.h>
#include <string.h>

static const char stop_arg[] = 
    {' ', '\t', '\0', ';', '&', '>', '<', '\0'};

void free_arr(char **arr)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);    
}

static bool stop(char c)
{
    for (size_t i = 0; stop_arg[i] != '\0'; i++) {
        if (stop_arg[i] == c)
            return true;
    }
    return false;
}

static char *get_last_path2(char *str, char *new, int x)
{
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
    char *new_str = NULL;

    if (str == NULL)
        return NULL;
    if (str[0] == '\0')
        return NULL;
    x = strlen(str) - 1;
    while (x != 0) {
        len++;
        if (stop(str[x]))
            break;
        x--;
    }
    new_str = malloc(sizeof(char) * (len + 1));
    return get_last_path2(str, new_str, x);
}

static void add_change(struct history_t *buff, char *path)
{
    size_t len = strlen(buff->str);
    char *temp;

    while (len != 0) {
        if (stop(buff->str[len]))
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

bool autocomplete(struct line_h *data, struct history_t *buff,
    struct history_t **history)
{
    char **new_list = NULL;
    char *path = get_last_path(buff->str);
    char *cmp = strdup(path);
    
    if (buff->temp != NULL)
        (*history) = change_the_buff(buff, *history);
    new_list = manager_get_file(&path);
    if (strcmp(cmp, path) != 0)
        add_change(buff, path);
    free(path);
    free(cmp);
    free_arr(data->autocomplete);
    data->autocomplete = new_list;
    return true;
}