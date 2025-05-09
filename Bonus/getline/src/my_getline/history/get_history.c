/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** get_usr
*/

#include "my_getline.h"
#include <stdio.h>

struct history_t *add_new_buff(struct history_t *history)
{
    struct history_t *new = malloc(sizeof(struct history_t));

    new->id = 0;
    new->str = NULL;
    new->before = NULL;
    new->temp = NULL;
    new->next = history;
    history->before = new;
    return new;
}

char *get_history_path(void)
{
    char *home = getenv("HOME");
    char *str = my_str_cmb(home, "/.bash_history");

    return str;
}

void print_history(struct history_t *history)
{
    if (history == NULL)
        return;
    print_history(history->next);
    printf("%li  %s\n", history->id, history->str);
}

void free_history(struct history_t *history)
{
    if (history == NULL)
        return;
    free_history(history->next);
    if (history->temp != NULL)
        free(history->temp);
    if (history->str != NULL)
        free(history->str);
    free(history);
}

static struct history_t *read_history(char **data, size_t x,
    struct history_t *history)
{
    struct history_t *new;

    if (data[x] == NULL) {
        free(data);
        return history;
    }
    new = malloc(sizeof(struct history_t));
    new->before = NULL;
    new->str = data[x];
    new->temp = NULL;
    new->id = x + 1;
    if (history == NULL) {
        new->next = NULL;
        return read_history(data, x + 1, new);
    }
    new->next = history;
    history->before = new;
    return read_history(data, x + 1, new);
}

struct history_t *get_history(void)
{
    char *path = get_history_path();
    char *file = open_file(path);
    char **data = NULL;

    if (path == NULL)
        return NULL;
    free(path);
    if (file == NULL)
        return NULL;
    data = my_str_to_word_array(file, "\n");
    free(file);
    return read_history(data, 0, NULL);
}
