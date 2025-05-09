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

static bool is_a_point(char *str, char *end)
{
    int len_str = strlen(str);
    int len_end = strlen(end);

    if (len_end > len_str)
        return false;
    while (len_end != -1) {
        if (str[len_str] != end[len_end])
            return false;
        len_str--;
        len_end--;
    }
    return true;
}

static void print_orange(char *str, int max_size)
{
    printf(" %s%-*s%s", YELLOW, max_size, str, RESET);
}

static void print_blue(char *str, int max_size)
{
    printf(" %s%-*s%s", BLUE, max_size, str, RESET);
}

static void print_green(char *str, int max_size)
{
    printf(" %s%s%-*s%s", BOLD, GREEN, max_size, str, RESET);
}

void print_auto2(char *str, int max_size, size_t type)
{
    if (type == F_DIR) {
        print_blue(str, max_size);
        return;
    }
    if (type == EXEC) {
        print_green(str, max_size);
        return;
    }
    if (strcmp(str, "Makefile") == 0) {
        print_orange(str, max_size);
        return;
    }
    if (is_a_point(str, ".h") || is_a_point(str, ".a") ||
        is_a_point(str, ".c")) {
        print_orange(str, max_size);
        return;
    }
    printf(" %-*s", max_size, str);
}

void print_auto(struct autoc_h *file, int max_size, size_t x, size_t selected)
{
    if (x + 1 == selected) {
        printf(" %s%s%-*s%s", BG_WHITE, BLACK, max_size, file->str, RESET);
        return;
    }
    print_auto2(file->str, max_size, file->type);
}
