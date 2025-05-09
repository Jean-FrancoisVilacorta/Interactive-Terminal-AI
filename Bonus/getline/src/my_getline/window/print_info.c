/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** print_line
*/

#include "my_getline.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

static const char *ia_activate =
" %s%sIA Activate%s Make your demand to the %s%sGarmentMaker%s~";

void print_info(struct line_h *data)
{
    int len = data->len;
    char spaces[len];

    printf("%s%s~%s%s", BOLD, MAGENTA, data->path, RESET);
    if (data->git == true) {
        printf(" %s%sgit:(%s%s%s)%s",
            BOLD, GREEN, YELLOW, data->branch, GREEN, RESET);
        len = len - 6 - strlen(data->branch);
    }
    len = len - strlen(data->path + 1) - strlen(data->time) - 3;
    spaces[0] = '\0';
    for (size_t i = 0; len > 0; i++) {
        spaces[i] = ' ';
        spaces[i + 1] = '\0';
        len--;
    }
    printf("%s%s\n", spaces, data->time);
    printf("˚₊%s%s%s· ͟͟͞͞➳❥ ", BLUE, data->usr, RESET);
}

void print_line(struct line_h *data, struct history_t *buff)
{
    size_t len = 0;
    int lines = 0;

    if (buff->temp != NULL)
        len = my_strlen(buff->temp) + my_strlen(data->usr) + 8;
    else
        len = my_strlen(buff->str) + my_strlen(data->usr) + 8;
    autocomplete_lines(data, buff);
    lines = GET_LINES_NEEDED(len, data->len);
    remove_lines(lines + data->auto_lines);
    printf("˚₊%s%s%s· ͟͟͞͞➳❥ ", BLUE, data->usr, RESET);
}

static size_t print_str(char *str, struct line_h *data)
{
    size_t len = my_strlen(data->usr) + 8;
    size_t lines = 1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (data->len == len) {
            printf("\n");
            len = 0;
            lines++;
        }
        printf("%c", str[i]);
        len++;
    }
    return lines;
}

static void print_autocomplete(struct line_h *data, size_t lines)
{
    struct autoc_h *file = data->autocomplete;
    size_t max_height = get_height() - lines;
    int max_size = get_max_size(data->autocomplete, 0) + 1;
    size_t how_many_str = (size_t)(data->len / max_size);

    printf("\n");
    for (size_t i = 0; i != max_height; i++) {
        for (size_t a = 0; a != how_many_str && file != NULL; a++) {
            print_auto(file, max_size, a, data->column);
            file = file->next;
        }
        if (file == NULL) {
            data->auto_lines = i + 1;
            return;
        }
        printf("\n");
    }
}

void print_buff(struct line_h *data, struct history_t *buff)
{
    size_t lines = 0;
    size_t len = 0;

    if (buff->temp != NULL) {
        print_str(buff->temp, data);
        return;
    }
    if (buff->str != NULL) {
        lines = print_str(buff->str, data);
        len = strlen(buff->str);
    }
    if (len == 1 && buff->str[0] == '#') {
        if (printf(ia_activate,
            BOLD, MAGENTA, RESET, BOLD, YELLOW, RESET) < 0)
                return;
    }
    if (data->autocomplete != NULL) {
        print_autocomplete(data, lines);
    }
}
