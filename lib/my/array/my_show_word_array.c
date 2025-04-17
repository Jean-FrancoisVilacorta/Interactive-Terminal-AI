/*
** EPITECH PROJECT, 2024
** my_show_word_array
** File description:
** show every words of an array
*/

#include "my.h"

int my_show_word_array(char *const *tab)
{
    int index = 0;

    while (tab[index] != 0){
        my_putstr(tab[index]);
        my_putchar('\n');
        index++;
    }
    return 0;
}
