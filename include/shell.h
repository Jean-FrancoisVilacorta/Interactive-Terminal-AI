/*
** EPITECH PROJECT, 2025
** header
** File description:
** minishell
*/

#ifndef HEADER
    #define HEADER
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define FAIL -1
    #define SUCCESS 0
    #define STDOUT_FD 1
    #define STDERR_FD 2
    #define OPEN 1
    #define CONTINUE 2
    #define WRITE 1
    #define READ 0
    #define NB_REDIRECTOR 6
    #define PRINT_ALIAS 1
    #define INVALID_ALIAS 2
    #define UNUSED __attribute_maybe_unused__
    #define GRAS(STR) "\033[1m"STR "\033[0m"
    #define CYAN(STR) "\x1b[34m"STR "\x1b[0m"
    #define ROUGE(STR) "\x1b[31m" STR "\x1b[0m"
    #define BLUE(STR) GRAS(CYAN(STR))
    #define RED(STR) GRAS(ROUGE(STR))
    #include <stdlib.h>
    #include "my.h"
    #include "bintree.h"
    #include <string.h>
    #include <stdbool.h>

typedef struct builtin_s {
    char *name;
    int(*func)();
} builtin_t;

typedef struct redirector_s {
    char *redirector;
    int (*function)(bintree_t *node, char ***env, int *status);
}redirector_t;

typedef struct alias_s alias_t;
struct alias_s {
    char *shortcut;
    char *command;
    alias_t *next;
};

int my_pipe(bintree_t *node, char ***env, int *status);
int redirect_input(bintree_t *node, char ***env, int *status);
int redirect_output(bintree_t *node, char ***env, int *status);
int redirect_output_double(bintree_t *node, char ***env, int *status);
int redirect_err_output(bintree_t *node, char ***env, int *status);

static const redirector_t redirectors[NB_REDIRECTOR] = {
    {">", &redirect_output},
    {">>", &redirect_output_double},
    {"<", &redirect_input},
    {"<<", NULL},
    {"|", &my_pipe},
    {"2>", &redirect_err_output}
};

alias_t **get_list_alias(void);

bool pipe_is_alone(char **all_commands);
int is_command_valid(char **all_commands);
int exec_all_commands(char *command_line, char ***env);
int shell_loop(char ***env, int is_tty);
int exec_builtin(char **commands, char ***env);
char *get_variable_from_command(char **command);
char *get_variable_name(char *commands);
char *get_env_variable(char **env, char *name);
int exist_in_env(char ***env, char *commands);
int builtin_env(char ***env);
int builtin_setenv(char ***env, char **commands);
int builtin_unsetenv(char ***env, char **commands);
int builtin_cd(char ***env, char **commands);
int builtin_alias(UNUSED char ***env, char **commands);
int builtin_unalias(UNUSED char ***env, char **commands);
int print_signal(int status);
int execute_tree(bintree_t *tree, char ***env, int *status);

static const builtin_t builtin_command[7] = {
    {"cd", &builtin_cd},
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"alias", &builtin_alias},
    {"unalias", &builtin_unalias},
    {NULL, NULL}
};

bintree_t *fill_tree(char *commands);

int check_file_access(char *path);
char *handle_command_not_exist(char *cmd);
char *handle_direct_binary(char *cmd);
int is_direct_path(char *cmd);
char *is_an_alias(char *command);

#endif
