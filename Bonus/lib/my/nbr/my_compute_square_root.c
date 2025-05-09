/*
** EPITECH PROJECT, 2024
** my_compute_square_root
** File description:
** square root
*/
#include "my.h"
int my_compute_square_root(int nb)
{
    int i = 0;

    while (i <= nb){
        if (my_compute_power_rec(i, 2) == nb){
            return i;
        }
        i++;
    }
    return 0;
}
