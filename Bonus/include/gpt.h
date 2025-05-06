/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** AI
*/

#ifndef INCLUDED_AI_H
    #define INCLUDED_AI_H
    #define FAIL         2
    #define SUCCESS      0
    #define EXIT_ERROR   84
    #define EXIT_SUCCESS 0
    #define STOP_ERROR   -1
    #define FINISH        1
    #define END          -1
    #define ERROR        -1
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

char *create_api_key(char *path);
char *verify_key(void);
int gpt_demand(char *demand);

#endif
