/*
** EPITECH PROJECT, 2025
** count_word
** File description:
** str_to_word_aray
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void print_array(char **array)
{
    if (!array)
        return;
    for (size_t i = 0; array[i]; i++)
        my_dprintf(0, "[ %s ]\n", array[i]);
}
