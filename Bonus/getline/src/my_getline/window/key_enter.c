/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** key_enter
*/

#include "my_getline.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

static size_t end_path(char *str)
{
    size_t end = strlen(str) - 1;

    if (str[0] == '\0')
        return 0;
    while (end != 0) {
        if (stop(str[end]) || str[end] == '/')
            return end + 1;
        end--;
    }
    return end;
}

static char *combine_with_path(char *str1, char *str2)
{
    size_t end = end_path(str1);
    char *temp = NULL;

    str1[end] = '\0';
    temp = my_str_cmb(str1, str2);
    free(str1);
    return temp;
}

static bool change_the_buff_from_file(struct history_t *buff,
    struct autoc_h *file)
{
    char *temp = NULL;

    if (buff->str == NULL)
        buff->str = strdup(file->str);
    else
        buff->str = combine_with_path(buff->str, file->str);
    if (buff->str == NULL)
        return false;
    if (file->type == F_DIR) {
        temp = my_str_cmb(buff->str, "/");
        free(buff->str);
        buff->str = temp;
    }
    return true;
}

static bool add_auto_to_buff(struct history_t *buff, struct autoc_h *file,
    size_t id, size_t x)
{
    if (id == x)
        return change_the_buff_from_file(buff, file);
    if (file == NULL)
        return false;
    return add_auto_to_buff(buff, file->next, id, x + 1);
}

bool analize_enter(struct line_h *data, struct history_t *buff,
    struct history_t **history, char *c)
{
    if (buff->temp != NULL)
        (*history) = change_the_buff(buff, *history);
    if (data->autocomplete != NULL) {
        if (add_auto_to_buff(buff, data->autocomplete,
            data->column, 1) == false) {
            free_auto(data->autocomplete);
            return false;
        }
        free_auto(data->autocomplete);
        data->autocomplete = NULL;
        *c = 'a';
    }
    return true;
}
