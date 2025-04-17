/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** shell
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#ifndef INCLUDED_SHELL_H
    #define INCLUDED_SHELL_H
    #define FAIL         2
    #define SUCCESS      0
    #define EXIT_ERROR   84
    #define EXIT_SUCCESS 0
    #define STOP_ERROR   -1
    #define FINISH        1
    #define END          -1
    #define RESET        "\033[0m"
    #define BLACK        "\033[30m"
    #define RED          "\033[31m"
    #define GREEN        "\033[32m"
    #define YELLOW       "\033[33m"
    #define BLUE         "\033[34m"
    #define MAGENTA      "\033[35m"
    #define CYAN         "\033[36m"
    #define WHITE        "\033[37m"
    #define BG_BLACK     "\033[40m"
    #define BG_RED       "\033[41m"
    #define BG_GREEN     "\033[42m"
    #define BG_YELLOW    "\033[43m"
    #define BG_BLUE      "\033[44m"
    #define BG_MAGENTA   "\033[45m"
    #define BG_CYAN      "\033[46m"
    #define BG_WHITE     "\033[47m"
    #define BOLD         "\033[1m"
    #define GET_LINES_NEEDED(len, width) (((len) + (width) - 1) / (width))

typedef struct line_h {
    char *usr;
    char *time;
    char *path;
    bool git;
    char *branch;
    char *first_line;
    char *name;
    size_t len;
} line_t;

typedef struct history_t {
    char *str;
    size_t id;
    char *temp;
    struct history_t *next;
    struct history_t *before;
} history_t;

char *my_getline(char *path);
struct line_h get_data(char *path);
struct history_t *get_history(void);
void free_history(struct history_t *history);
void free_data(struct line_h *data);
bool special_key(struct line_h *data, struct history_t **history,
    char c, struct history_t *buff);
struct history_t *change_the_buff(struct history_t *buff,
    struct history_t *history);
struct history_t *add_new_buff(struct history_t *history);
int get_termianl_len(void);
void print_buff(struct line_h *data, struct history_t *buff);
void print_line(struct line_h *data, struct history_t *buff);
void print_info(struct line_h *data);
void remove_lines(int n);

#endif
