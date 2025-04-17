/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** reverse an string
*/
#include <unistd.h>
#include "my.h"

char *my_revstr(char *str)
{
    int size = my_strlen(str);
    int i;
    char T;
    char *first;
    char *last;

    for (i = 0; i < size / 2; i++) {
        first = &str[i];
        last = &str[size - i - 1];
        T = *first;
        *first = *last;
        *last = T;
        }
    return str;
}
