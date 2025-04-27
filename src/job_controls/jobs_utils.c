/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** jobs_utils
*/

#include "shell.h"
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

job_t **get_jobs_list(void)
{
    static job_t *jobs = NULL;

    return &jobs;
}

int get_next_job_number(job_t *jobs)
{
    int max_num = 0;
    job_t *current = jobs;

    while (current) {
        if (current->number > max_num)
            max_num = current->number;
        current = current->next;
    }
    return max_num + 1;
}

static void print_job_info(job_t *job)
{
    my_dprintf(STDOUT_FD, "[%d] %d\n", job->number, job->pid);
}

job_t *add_job(job_t **jobs, pid_t pid, char *cmd)
{
    job_t *new = malloc(sizeof(job_t));
    job_t *current = *jobs;

    if (!new)
        return NULL;
    new->pid = pid;
    new->status = 0;
    new->command = strdup(cmd);
    new->number = get_next_job_number(*jobs);
    new->next = NULL;
    if (!*jobs) {
        *jobs = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
    print_job_info(new);
    return new;
}

void update_job_status(job_t **jobs)
{
    job_t *job = *jobs;
    job_t *next = NULL;
    int status;
    pid_t pid;

    while (job) {
        next = job->next;
        pid = waitpid(job->pid, &status, WNOHANG | WUNTRACED);
        if (pid > 0 && !WIFSTOPPED(status) && !WIFCONTINUED(status))
            remove_job(jobs, job->pid);
        if (pid > 0)
            job->status = status;
        job = next;
    }
}

void remove_job(job_t **jobs, pid_t pid)
{
    job_t *current = *jobs;
    job_t *prev = NULL;

    if (!current)
        return;
    if (current->pid == pid) {
        *jobs = current->next;
        free(current->command);
        free(current);
        return;
    }
    while (current && current->pid != pid) {
        prev = current;
        current = current->next;
    }
    if (current) {
        prev->next = current->next;
        free(current->command);
        free(current);
    }
}
