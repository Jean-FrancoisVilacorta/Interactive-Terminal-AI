/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** copy an string
*/

#include <unistd.h>

char *my_strcpy(char *dest, char const *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
