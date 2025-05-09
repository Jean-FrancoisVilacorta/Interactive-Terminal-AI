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

int get_terminal_width(void)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

static void desactivate_termianl(struct termios *old_termios)
{
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, old_termios);
    new_termios = *old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

struct history_t *change_the_buff(struct history_t *buff,
    struct history_t *history)
{
    if (history->before != NULL)
        return change_the_buff(buff, history->before);
    if (buff->str != NULL)
        free(buff->str);
    buff->str = buff->temp;
    buff->temp = NULL;
    return history;
}

static bool add_to_buffer(struct line_h *data, struct history_t *buff,
    struct history_t **history, char c)
{
    size_t size = 0;
    char *last_path = NULL;

    if (buff->temp != NULL)
        (*history) = change_the_buff(buff, *history);
    buff->str = my_realloc(buff->str);
    size = my_strlen(buff->str);
    if (buff->str == NULL)
        return false;
    buff->str[size] = c;
    buff->str[size + 1] = '\0';
    last_path = get_end(buff->str);
    if (last_path == NULL)
        return true;
    data->autocomplete = modify_auto(data->autocomplete, last_path);
    data->column = 0;
    free(last_path);
    return true;
}

static bool analize_char(struct line_h *data, char *c,
    struct history_t *buff, struct history_t **history)
{
    if (!special_key(data, history, c, buff))
        if (!add_to_buffer(data, buff, history, *c))
            return false;
    return true;
}

static char *read_line(struct line_h *data,
    struct history_t *buff, struct history_t *history)
{
    char c = '\0';

    while (1) {
        c = getchar();
        print_line(data, buff);
        if (!analize_char(data, &c, buff, &history))
            return NULL;
        print_buff(data, buff);
        if (c == '\n' || c == '\0')
            break;
    }
    if (data->autocomplete != NULL)
        free_auto(data->autocomplete);
    return buff->str;
}

char *my_getline(char *path)
{
    struct termios old_termios;
    struct line_h data = get_data(path);
    struct history_t *history = get_history();
    struct history_t *new = add_new_buff(history);
    char *ret = NULL;

    data.len = get_termianl_len();
    desactivate_termianl(&old_termios);
    print_info(&data);
    ret = read_line(&data, new, new);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    replace_h(new);
    free_history(history);
    free_data(&data);
    free(new->temp);
    free(new);
    printf("\n");
    return ret;
}
