/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "my_getline.h"
#include <unistd.h>
#include <stdlib.h>

static char *end(char *buffer, size_t size)
{
    if (size > 0)
        buffer[size] = '\0';
    return buffer;
}

char *my_getlinea(void)
{
    char *buffer = NULL;
    char c;
    size_t size = 0;

    while (read(0, &c, 1) > 0) {
        buffer = my_realloc(buffer);
        buffer[size] = c;
        if (c == '\n' || c == '\0')
            return end(buffer, size);
        if (buffer == NULL) {
            free(buffer);
            return NULL;
        }
        size++;
    }
    if (buffer != NULL)
        return buffer;
    return NULL;
}
