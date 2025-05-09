/*
** EPITECH PROJECT, 2024
** search_rec.c
** File description:
** search a rectangle in the map
*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "my_getline.h"

static int file_size(char const *filepath)
{
    struct stat st;
    int size = 0;

    if (stat(filepath, &st) == -1)
        return ERROR_INT;
    size = st.st_size;
    return size;
}

static int verify_first_errors(int fd, int filesize)
{
    if (fd == ERROR_INT) {
        return -1;
    }
    if (filesize == ERROR_INT || filesize == 0) {
        my_dputstr(2, "[ERROR] Unable to get file size\n");
        return -1;
    }
    return SUCCESS;
}

char *open_file(char const *filepath)
{
    int fd = open(filepath, O_RDONLY);
    size_t line_size = 0;
    int filesize = file_size(filepath);
    char *buffer = NULL;

    if (verify_first_errors(fd, filesize) == -1)
        return NULL;
    buffer = malloc(sizeof(char) * filesize + 1);
    if (buffer == NULL) {
        my_dputstr(2, "[ERROR] Unable to allocate memory\n");
        return NULL;
    }
    line_size = read(fd, buffer, filesize);
    if (line_size == (size_t)-1) {
        my_dputstr(2, "[ERROR] Unable to read file\n");
        return NULL;
    }
    buffer[filesize] = '\0';
    close(fd);
    return buffer;
}
