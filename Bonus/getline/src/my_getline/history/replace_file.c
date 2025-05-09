/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** replace
*/

#include "my_getline.h"
#include <stdio.h>

int write_in_file(struct history_t *history, FILE *file)
{
    if (history == NULL)
        return SUCCESS;
    if (write_in_file(history->next, file) == FAIL)
        return FAIL;
    if (fprintf(file, "%s\n", history->str) < 0)
        return FAIL;
    return SUCCESS;
}

int replace_file(char *path, struct history_t *history)
{
    FILE *file = fopen(path, "w");
    int ret = SUCCESS;

    free(path);
    if (!file)
        return FAIL;
    ret = write_in_file(history, file);
    fclose(file);
    return ret;
}

int replace_h(struct history_t *history)
{
    char *file_path = get_history_path();

    if (file_path == NULL)
        return FAIL;
    return replace_file(file_path, history);
}
