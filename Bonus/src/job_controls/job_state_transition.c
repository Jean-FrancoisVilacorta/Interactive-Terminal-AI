/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** job_state_transition
*/

#include "shell.h"
#include <signal.h>
#include <termios.h>
#include <sys/wait.h>

static void set_foreground_process(pid_t pid)
{
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pid);
    signal(SIGTTOU, SIG_DFL);
}

static void display_suspended_msg(UNUSED char *cmd)
{
    my_dprintf(STDOUT_FD, "\nSuspended\n");
}

int put_job_in_foreground(job_t *job)
{
    int status;

    if (!job)
        return FAIL;
    set_foreground_process(job->pid);
    kill(-job->pid, SIGCONT);
    my_dprintf(STDOUT_FD, "%s\n", job->command);
    waitpid(job->pid, &status, WUNTRACED);
    if (WIFSTOPPED(status)) {
        display_suspended_msg(job->command);
        job->status = status;
    } else
        remove_job(get_jobs_list(), job->pid);
    set_foreground_process(getpid());
    return SUCCESS;
}

int put_job_in_background(job_t *job)
{
    if (!job)
        return FAIL;
    kill(-job->pid, SIGCONT);
    job->status = 0;
    my_dprintf(STDOUT_FD, "[%d] %d\n", 1, job->pid);
    return SUCCESS;
}
