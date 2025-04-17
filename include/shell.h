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
    #define UNUSED __attribute_maybe_unused__
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
int print_signal(int status);
int execute_tree(bintree_t *tree, char ***env, int *status);

static const builtin_t builtin_command[5] = {
    {"cd", &builtin_cd},
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {NULL, NULL}
};

bintree_t *fill_tree(char *commands);


int check_file_access(char *path);
#endif
