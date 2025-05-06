/*
** EPITECH PROJECT, 2025
** lib
** File description:
** delete element array
*/

#include <stdlib.h>
#include <stdio.h>

void delete_element_array(char **array, int index)
{
    size_t i = 0;

    for (i = index; array[i] != NULL; i++)
        array[i - 1] = array[i];
    array[i - 1] = NULL;
}
