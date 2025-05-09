/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** special_keys
*/

#include "my_getline.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

static bool remove_last(struct history_t *buff,
    struct history_t **history)
{
    size_t len = 0;

    if (buff->temp != NULL)
        (*history) = change_the_buff(buff, *history);
    len = my_strlen(buff->str);
    if (buff->str == NULL || len == 0)
        return true;
    if (buff->str[1] == '\0') {
        buff->str[0] = '\0';
        return true;
    }
    if (len > 0)
        buff->str[len - 1] = '\0';
    return true;
}

static void remplace(struct history_t *history,
    struct history_t *buff)
{
    if (buff->temp != NULL)
        free(buff->temp);
    buff->temp = my_strcpy(history->str);
}

static struct history_t *key_up(struct history_t *history,
    struct history_t *buff, struct history_t *start)
{
    if (buff->str != NULL) {
        if (buff->str[0] == '\0' ||
            my_strncmp(buff->str, history->str, strlen(buff->str)) == 0) {
            remplace(history, buff);
            return history;
        }
        if (history->next != NULL)
            return key_up(history->next, buff, start);
        return start;
    }
    remplace(history, buff);
    return history;
}

static struct history_t *key_down(struct history_t *history,
    struct history_t *buff, struct history_t *start)
{
    if (buff->str != NULL) {
        if (buff->str[0] == '\0' ||
            my_strncmp(buff->str, history->str, strlen(buff->str)) == 0) {
            remplace(history, buff);
            return history;
        }
        if (history->before != NULL)
            return key_down(history->before, buff, start);
        return start;
    }
    remplace(history, buff);
    return history;
}

static bool key_movement(struct history_t **history,
    char c, struct history_t *buff)
{
    if (c == 65) {
        if ((*history)->next != NULL) {
            *history = key_up((*history)->next, buff, *history);
        }
        return true;
    }
    if (c == 66) {
        if ((*history)->before != NULL) {
            *history = key_down((*history)->before, buff, *history);
        }
        return true;
    }
    return true;
}

bool special_key(struct line_h *data, struct history_t **history,
    char *c, struct history_t *buff)
{
    if (*c == ENTER)
        return analize_enter(data, buff, history, c);
    if (*c == AUTOCOMPLETE)
        return autocomplete(data, buff, history);
    if (*c == DELETE) {
        free_auto(data->autocomplete);
        data->autocomplete = NULL;
        return remove_last(buff, history);
    }
    if (*c == SPECIAL_KEY) {
        *c = getchar();
        if (*c == ARROW) {
            *c = getchar();
            key_movement(history, *c, buff);
            return true;
        }
        getchar();
    }
    return false;
}
