/*
** EPITECH PROJECT, 2025
** count_word
** File description:
** str_to_word_aray
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

size_t my_array_len(char **array)
{
    size_t len = 0;

    if (!array)
        return 0;
    for (len = 0; array[len]; len++);
    return len;
}
