/*
** EPITECH PROJECT, 2025
** Minishell (Workspace)
** File description:
** shell
*/

#include <stddef.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>

#ifndef INCLUDED_SHELL_H
    #define INCLUDED_SHELL_H
    #define FAIL 1
    #define SUCCESS 0
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define STOP_ERROR -1

typedef struct redirections_s {
    char *flag;
}redirections_t;

static const redirections_t redirections[] = {
    {">"},
    {">>"},
    {"<"},
    {"<<"},
    {"|"},
    {NULL},
};

typedef struct command_s {
    char *command;
    char **ouput;
    char *flag;
    int fd;
    struct command_s *next;
    struct command_s *before;
} command_t;

typedef struct dividers_s {
    char *flag;
    struct command_s *commands;
    struct dividers_s *next;
} dividers_t;


typedef struct shell_s {
    char **env;
    char *pwd;
    char *oldpwd;
    char *home;
    char **path;
    int exit;
    struct dividers_s *dividers;
}shell_t;

struct flag_s {
    char *command;
    int (*func)(shell_t *shell, command_t *command);
};

int env(shell_t *shell, command_t *command);
int cdirectory(shell_t *shell, command_t *command);
int exit_shell(shell_t *shell, command_t *command);
int my_unsetenv(shell_t *shell, command_t *command);
int my_setenv(shell_t *shell, command_t *command);
int default_command(shell_t *shell, command_t *command);

static const struct flag_s flag[] = {
    {"exit", exit_shell},
    {"cd", cdirectory},
    {"env", env},
    {"unsetenv", my_unsetenv},
    {"setenv", my_setenv},
    {"\n", NULL},
};

int prepare_shell(char const *const *env);
void double_free(char **array);
void free_shell(shell_t *shell);
void free_dividers(dividers_t *div);
void free_commands(command_t *commands);
dividers_t *struct_commands(char const *str, char *a);
bool search_redir(char const *str);
bool search_dividers(char const *str);
bool correct_format(char **arr, int i, bool separators, bool pipes);
int organize_command_struct(char **arr, int i, command_t *command);
char *get_env(char const *src, char const *const *env);
int get_env_x(char const *src, char const *const *env);
char *get_env_data(char const *src, char const *const *env);
int analyze_ouput(shell_t *shell, char *ouput);
int print_env(int const fd, char const *const *env);
int set_env(shell_t *shell, char **ouputs);
char **get_path(char const *const *env);
char *my_str_cmb_pwd(const char *str1, const char *str2);
int execute_commands(shell_t *shell, command_t *command, int prev_fd);
int pipe_command(shell_t *shell, command_t *command, int prev_fd);
int redirect_to_file(shell_t *shell, command_t *command, int prev_fd);
int run_prog(shell_t *shell, command_t *command);
int error_wait(const pid_t status, shell_t *shell,
    command_t *command, int new_fd);
int redirect_to_file_and_append(shell_t *shell,
    command_t *command, int prev_fd);
int send_file_to_exec(shell_t *shell, command_t *command,
    int prev_fd);
int read_to_exec(shell_t *shell, command_t *command, int prev_fd);
int default_info(shell_t *shell, char const *const *env);

#endif
