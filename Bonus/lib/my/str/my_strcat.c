/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** conctenate 2 str
*/

#include "my.h"
char *my_strcat(char *dest, char const *src)
{
    int i = my_strlen(dest);
    int j = 0;

    if (!src || !dest)
        return NULL;
    while (src[j] != '\0'){
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return dest;
}
