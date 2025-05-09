/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** cmp 2 str until n
*/

#include "my.h"

static int check_length(char const *s1, char const *s2)
{
    if (my_strlen(s1) < my_strlen(s2)){
        return -1;
    } else if (my_strlen(s1) > my_strlen(s2)){
        return 1;
    }
    return 0;
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && n > 0){
        if (s1[i] < s2[i]){
            return -1;
        }
        if (s1[i] > s2[i]){
            return 1;
        }
        i++;
        n--;
    }
    if (n <= 0){
        return 0;
    }
    return check_length(s1, s2);
}
