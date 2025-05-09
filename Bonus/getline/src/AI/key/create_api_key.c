/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** create_api_key
*/

#include "gpt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *stock_key(char *path, char *key, size_t len)
{
    FILE *file = fopen(path, "w");

    if (!file) {
        free(key);
        free(path);
        return NULL;
    }
    if (fwrite(key, 1, len, file) == 0) {
        fclose(file);
        free(path);
        free(key);
        printf("%s%sERROR when creating it\n%s", BOLD, RED, RESET);
        return NULL;
    }
    fclose(file);
    free(path);
    printf("%s%sCreated correctly\n%s", BOLD, GREEN, RESET);
    return key;
}

char *create_api_key(char *path)
{
    char *line = NULL;
    size_t len = 0;
    size_t read = 0;

    if (printf("Insert your API KEY:\n> ") < 0) {
        free(path);
        return NULL;
    }
    read = getline(&line, &len, stdin);
    if ((int)read == ERROR) {
        free(path);
        return NULL;
    }
    len = strlen(line);
    if (len > 0)
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
    return stock_key(path, line, read);
}
