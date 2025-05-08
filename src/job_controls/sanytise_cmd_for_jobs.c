/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** sanytise_cmd_for_jobs
*/

#include "shell.h"

int is_background(char *cmd)
{
    int len = my_strlen(cmd);

    return (len > 0 && cmd[len - 1] == '&');
}

char *trim_background(char *cmd)
{
    int len = my_strlen(cmd);

    while (len > 0 && (cmd[len - 1] == '&' || cmd[len - 1] == ' ')) {
        cmd[len - 1] = '\0';
        len--;
    }
    return cmd;
}

job_t *find_job(job_t **jobs, pid_t pid)
{
    job_t *current = *jobs;

    while (current) {
        if (current->pid == pid || current->number == pid)
            return current;
        current = current->next;
    }
    return NULL;
}
