/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** display one by one, the characters of a string
*/

#include <stddef.h>

size_t my_strstrlen(char **strstr)
{
    size_t len = 0;

    if (strstr == NULL)
        return 0;
    while (strstr[len] != NULL)
        len++;
    return len;
}

size_t my_strlen(char const *str)
{
    size_t count = 0;

    if (str == NULL)
        return 0;
    while (str[count] != '\0')
        count++;
    return count;
}
