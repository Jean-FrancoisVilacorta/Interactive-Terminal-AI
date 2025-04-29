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
    #include <sys/types.h>

typedef struct builtin_s {
    char *name;
    int(*func)();
} builtin_t;

typedef enum inhibitor_s {
    DOUBLE_QUOTE = 1,
    SINGLE_QUOTE = 2
} inhibitor_t;

typedef struct redirector_s {
    char *redirector;
    int (*function)(bintree_t *node, char ***env, int *status);
} redirector_t;

typedef struct alias_s alias_t;
struct alias_s {
    char *shortcut;
    char *command;
    alias_t *next;
};

typedef struct foreach_s foreach_t;
struct foreach_s {
    char *command;
    foreach_t *next;
};

alias_t **get_list_alias(void);

typedef struct job_s {
    pid_t pid;
    char *command;
    int status;
    int number;
    struct job_s *next;
} job_t;

// JOBS CONTROLS:
int is_background(char *cmd);
char *trim_background(char *cmd);
job_t *add_job(job_t **jobs, pid_t pid, char *cmd);
void remove_job(job_t **jobs, pid_t pid);
void update_job_status(job_t **jobs);
job_t **get_jobs_list(void);
int get_next_job_number(job_t *jobs);
int builtin_jobs(UNUSED char ***env, UNUSED char **args);
int builtin_fg(UNUSED char ***env, char **args);
int builtin_bg(UNUSED char ***env, char **args);
job_t *find_job_by_pid(job_t **jobs, pid_t pid);
int put_job_in_foreground(job_t *job);
int put_job_in_background(job_t *job);

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

size_t my_strnlen(char const *str, size_t n);
char *dollars_signe(char ***env, char *line);
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
int builtin_repeat(char ***env, char **commands);
int builtin_foreach(char ***env, char **commands);
int print_signal(int status);
int execute_tree(bintree_t *tree, char ***env, int *status);
char **find_globbings(char **cmds, char *path);

static const builtin_t builtin_command[12] = {
    {"cd", &builtin_cd},
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"alias", &builtin_alias},
    {"unalias", &builtin_unalias},
    {"foreach", &builtin_foreach},
    {"repeat", &builtin_repeat},
    {"jobs", &builtin_jobs},
    {"fg", &builtin_fg},
    {"bg", &builtin_bg},
    {NULL, NULL}
};

bool is_inquote(char *command);
char *manage_inhibitor(char *command);

bintree_t *fill_tree(char *commands);

int check_file_access(char *path);
int check_basic_access(char *path);
char *handle_command_not_exist(char *cmd);
char *handle_direct_binary(char *cmd);
int is_direct_path(char *cmd);
char *is_an_alias(char *command);

#endif
