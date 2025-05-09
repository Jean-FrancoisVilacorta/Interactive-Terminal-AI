/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** gpt_demand
*/

#include "gpt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

static int exec_gpt(char *key, char *request, size_t len)
{
    char comand[len + 20];
    int result = 0;

    snprintf(comand, sizeof(comand),
        "/bin/gpt.py \"%s\" \"%s\"", key, request);
    result = system(comand);
    if (result == ERROR) {
        printf("The %s%sGarderMaker%s is not awake, try later\n",
            BOLD, YELLOW, RESET);
        free(key);
        return FAIL;
    }
    free(key);
    return SUCCESS;
}

int gpt_demand(char *demand)
{
    char *api_key = verify_key();
    size_t len = 0;

    if (api_key == NULL)
        return FAIL;
    len = strlen(api_key) + strlen(demand);
    return exec_gpt(api_key, demand, len);
}
