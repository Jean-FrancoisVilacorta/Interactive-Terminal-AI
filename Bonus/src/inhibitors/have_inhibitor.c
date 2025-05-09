/*
** EPITECH PROJECT, 2025
** shell
** File description:
** handle inhibitor
*/

#include "shell.h"

static int skip_inhibittor(char *command, int index, char inhibitor)
{
    int skip = index + 1;

    while (command[skip] && command[skip] != inhibitor){
        skip++;
    }
    if (!command[skip]){
        my_dprintf(STDERR_FD, "Unmatched \'%c\'.\n", inhibitor);
        return FAIL;
    }
    return skip - index;
}

static int check_inhibittor(char *command, int index)
{
    int skip = 0;

    if (command[index] == '\'' || command[index] == '\"'){
        skip = skip_inhibittor(command, index, command[index]);
    }
    if (skip == FAIL)
        return FAIL;
    return skip;
}

static int len_inhibitor(char *commands)
{
    int len = 0;
    int skip = 0;

    for (int i = 0; i < my_strlen(commands); ++i){
        skip = check_inhibittor(commands, i);
        if (skip == FAIL)
            return FAIL;
        if (skip != 0){
            len += skip - 1;
            i += skip;
            continue;
        }
        len++;
    }
    return len;
}

static char *remove_inhibitors(char *command, int new_len)
{
    char *new = malloc(sizeof(char) * (new_len + 1));
    int index = 0;
    char inhibitor = 0;

    if (!new)
        return NULL;
    for (int i = 0; i < my_strlen(command); i++){
        if ((command[i] == '\'' || command[i] == '\"') &&
            (inhibitor == 0 || inhibitor == command[i])){
            inhibitor = (inhibitor != 0) ? 0 : command[i];
            continue;
        }
        new[index] = command[i];
        index++;
    }
    new[new_len] = '\0';
    return new;
}

int have_inhibitor(char *commands)
{
    int new_len = len_inhibitor(commands);
    char *new = NULL;

    if (my_strlen(commands) == new_len)
        return SUCCESS;
    if (new_len == FAIL)
        return FAIL;
    new = remove_inhibitors(commands, new_len);
    if (!new)
        return FAIL;
    free(commands);
    commands = my_strdup(new);
    free(new);
    return SUCCESS;
}
