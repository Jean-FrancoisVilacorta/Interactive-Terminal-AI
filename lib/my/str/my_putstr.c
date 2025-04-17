/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** Write a function that displays, one-by-one, the characters of a string.
*/

#include "my.h"
#include <unistd.h>

int my_putstr(char const *str)
{
    int p = 0;

    while (str[p] != '\0') {
        my_putchar(str[p]);
        p++;
    }
    return p;
}
