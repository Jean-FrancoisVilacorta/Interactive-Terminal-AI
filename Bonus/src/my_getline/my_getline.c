/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** my_getline
*/

#include "my_getline.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

struct termios oldt, newt;

static void activate_raw(void)
{
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

static int get_termianl_len(void)
{
    struct winsize w;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return -1;
    return w.ws_col;
}

void print_line(struct line_h *data)
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

static char *read_line(void)
{
    char c = '\0';

    activate_raw();
    while (1) {
        c = getchar();
        if (c == 'q')
            break;
        printf("%c", c);
    }
    return 0;
}

char *my_getline(char *path)
{
    struct line_h data = get_data(path);
    char *ret = NULL;

    data.len = get_termianl_len();
    print_line(&data);
    ret = read_line();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ret;
}
