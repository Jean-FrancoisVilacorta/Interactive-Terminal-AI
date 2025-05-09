/*
** EPITECH PROJECT, 2024
** my_put_char
** File description:
** print letters
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_getline.h"

char *my_str_cmb(const char *str1, const char *str2)
{
    int long1 = my_strlen(str1);
    int long2 = my_strlen(str2);
    int i = 0;
    char *combined = malloc(sizeof(char) * (long1 + long2 + 1));

    if (combined == NULL)
        return NULL;
    for (i = 0; i < long1; i++) {
        combined[i] = str1[i];
    }
    for (int j = 0; j < long2; j++) {
        combined[i] = str2[j];
        i++;
    }
    combined[i] = '\0';
    return combined;
}
