/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** print_line
*/

#include "my_getline.h"
#include "lib.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

void remove_lines(int n)
{
    for (int i = 0; i < n; i++) {
        printf("\033[2K\r");
        if (i < n - 1) {
            printf("\033[1A");
        }
    }
    fflush(stdout);
}

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
    lines = GET_LINES_NEEDED(len, data->len);
    remove_lines(lines);
    printf("˚₊%s%s%s· ͟͟͞͞➳❥ ", BLUE, data->usr, RESET);
}

static void print_str(char *str, struct line_h *data)
{
    size_t len = my_strlen(data->usr) + 8;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (data->len == len) {
            printf("\n");
            len = 0;
        }
        printf("%c", str[i]);
        len++;
    }
}

void print_buff(struct line_h *data, struct history_t *buff)
{
    if (buff->temp != NULL) {
        print_str(buff->temp, data);
        return;
    }
    if (buff->str != NULL)
        print_str(buff->str, data);
}
