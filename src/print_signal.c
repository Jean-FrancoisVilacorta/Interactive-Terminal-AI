/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** print signal
*/

#include "shell.h"
#include "sys/wait.h"
#include <signal.h>

static void print_crash_signal(int status)
{
    if (WTERMSIG(status) == SIGSEGV && WCOREDUMP(status)){
        my_dprintf(STDERR_FD, "Segmentation fault (core dumped)\n");
        return;
    }
    if (WTERMSIG(status) == SIGSEGV)
        my_dprintf(STDERR_FD, "Segmentation fault\n");
    if (WTERMSIG(status) == SIGFPE && SIGFPE){
        my_dprintf(STDERR_FD, "Floating exception (core dumped)\n");
        return;
    }
    if (WTERMSIG(status) == SIGFPE)
        my_dprintf(STDERR_FD, "Floating exception\n");
}

int print_signal(int status)
{
    if (status == FAIL){
        my_dprintf(STDERR_FD, "waitpid failed\n");
        return FAIL;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)){
        print_crash_signal(status);
    }
    return status;
}
