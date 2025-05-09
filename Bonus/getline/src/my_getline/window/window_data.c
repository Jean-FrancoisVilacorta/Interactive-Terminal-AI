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

size_t get_height(void)
{
    struct winsize w;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return -1;
    }
    return w.ws_row;
}

int get_max_size(struct autoc_h *file, int max_size)
{
    int temp = 0;

    if (file == NULL)
        return max_size;
    temp = strlen(file->str);
    if (temp > max_size)
        max_size = temp;
    return get_max_size(file->next, max_size);
}

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
