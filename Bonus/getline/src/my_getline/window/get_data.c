/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** get_usr
*/

#include "my_getline.h"
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <sys/stat.h>
#include <limits.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

struct termios oldt, newt;

void free_data(struct line_h *data)
{
    if (data->time != NULL)
        free(data->time);
    if (data->git == true)
        free(data->branch);
}

int get_termianl_len(void)
{
    struct winsize w;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return -1;
    return w.ws_col;
}

static char *read_path_line(char *line)
{
    int len = strlen(line);
    char branch[len];

    if (strncmp(line, "ref: refs/heads/", strlen("ref: refs/heads/")) == 0) {
        strncpy(branch, line + strlen("ref: refs/heads/"), len);
        branch[strcspn(branch, "\n")] = '\0';
        return my_strcpy(branch);
    }
    return "HEAD (detached)";
}

static char *get_branch(char *path)
{
    int len = strlen(path) + 8;
    char headPath[len];
    char line[100];
    FILE *fp = NULL;

    snprintf(headPath, len, "%s/HEAD", path);
    fp = fopen(headPath, "r");
    if (fp == NULL)
        return NULL;
    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    return read_path_line(line);
}

static bool search_git(char *path, struct line_h *data)
{
    int len = strlen(path) + 10;
    char new_path[len + 1];
    struct stat st;
    char *slash = NULL;

    snprintf(new_path, len, "%s/.git", path);
    if (stat(new_path, &st) == 0 && S_ISDIR(st.st_mode)) {
        data->branch = get_branch(new_path);
        return true;
    }
    slash = strrchr(path, '/');
    if (slash == NULL || slash == path)
        return false;
    *slash = '\0';
    return search_git(path, data);
}

static char *cut_first(char *str)
{
    char *slash = strchr(str, '/');

    if (slash != NULL && *(slash + 1) != '\0')
        return slash + 1;
    return "";
}

static char *get_time(void)
{
    char act_time[256];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    setlocale(LC_TIME, "en_us.utf8");
    strftime(act_time, sizeof(act_time), "%A %B %d, %H:%M", tm_info);
    return my_strcpy(act_time);
}

static char *get_usr(void)
{
    struct passwd *pw = getpwuid(getuid());

    if (pw != NULL)
        return pw->pw_name;
    return "unknow";
}

static char *get_path(char *path)
{
    if (path == NULL)
        return NULL;
    while (strlen(path) > 70) {
        path = cut_first(path);
    }
    return path;
}

struct line_h get_data(char *path)
{
    struct line_h data;

    data.usr = get_usr();
    data.time = get_time();
    data.path = get_path(path);
    data.git = search_git(path, &data);
    data.autocomplete = NULL;
    data.auto_lines = 0;
    data.column = 0;
    return data;
}
