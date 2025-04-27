/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** jobs
*/

#include "shell.h"
#include <signal.h>
#include <sys/wait.h>

static void print_job_status(job_t *job)
{
    char *status = "Running";
    char *prefix = "-";

    if (WIFSTOPPED(job->status))
        status = "Suspended";
    if (job->number == 1)
        prefix = "+";
    my_dprintf(STDOUT_FD, "[%d] %s %s                       %s\n",
        job->number, prefix, status, job->command);
}

int builtin_jobs(UNUSED char ***env, UNUSED char **args)
{
    job_t **jobs = get_jobs_list();
    job_t *job = *jobs;

    update_job_status(jobs);
    while (job) {
        print_job_status(job);
        job = job->next;
    }
    return SUCCESS;
}
