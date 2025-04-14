/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** concatenate str
*/

#include "my.h"
char *my_strncat(char *dest, char const *src, int n)
{
    int i = my_strlen(dest);
    int j = 0;

    while (src[j] != '\0' && n != 0){
        dest[i + j] = src[j];
        j++;
        n--;
    }
    dest[i + j] = '\0';
    return dest;
}
