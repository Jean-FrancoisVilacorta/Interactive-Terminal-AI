/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** bg
*/

#include "shell.h"
#include <signal.h>
#include <sys/wait.h>

int builtin_bg(UNUSED char ***env, char **args)
{
    job_t **jobs = get_jobs_list();
    job_t *job;
    pid_t pid;

    if (!args[1]) {
        my_dprintf(STDERR_FD, "bg: no current job\n");
        return FAIL;
    }
    pid = atoi(args[1]);
    job = find_job(jobs, pid);
    if (!job) {
        my_dprintf(STDERR_FD, "bg: %s: No such job\n", args[1]);
        return FAIL;
    }
    kill(job->pid, SIGCONT);
    return SUCCESS;
}
