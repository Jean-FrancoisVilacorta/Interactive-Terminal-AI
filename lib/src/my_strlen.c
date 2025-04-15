/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** display one by one, the characters of a string
*/

#include <stddef.h>

int my_strstrlen(char const *const *strstr)
{
    int len = 0;

    if (strstr == NULL)
        return -1;
    while (strstr[len] != NULL)
        len++;
    return len;
}

int my_strlen(char const *str)
{
    int count = 0;

    if (str == NULL)
        return -1;
    while (str[count] != '\0')
        count++;
    return count;
}
