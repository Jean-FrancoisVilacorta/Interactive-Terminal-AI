/*
** EPITECH PROJECT, 2024
** my_strcapitalize
** File description:
** capitalize every word
*/
#include "my.h"

int not_number_or_letter(char c)
{
    if ((c > 96 && c < 123) || (c > 64 && c < 91)){
        return 0;
    }
    if (c < 58 && c > 47){
        return 0;
    }
    return 1;
}

int is_letter(char c)
{
    if (c > 96 && c < 123){
        return 1;
    }
    return 0;
}

char *my_strcapitalize(char *str)
{
    int i = 0;

    my_strlowcase(str);
    if (is_letter(str[0]) == 1){
        str[0] -= 32;
    }
    while (str[i] != 0){
        if (not_number_or_letter(str[i]) == 1 && is_letter(str[i + 1]) == 1){
            str[i + 1] -= 32;
        }
        i++;
    }
    return str;
}
