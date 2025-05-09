/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** autocomplete
*/

#include "my_getline.h"
#include <stdio.h>
#include <string.h>

size_t count_options(struct autoc_h *list, size_t x)
{
    if (list == NULL)
        return x;
    return count_options(list->next, x + 1);
}

bool change_column(struct line_h *data)
{
    size_t count_opt = count_options(data->autocomplete, 0);

    if (data->column >= count_opt)
        data->column = 1;
    else
        data->column++;
    return true;
}
