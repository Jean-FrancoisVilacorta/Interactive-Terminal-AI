/*
** EPITECH PROJECT, 2024
** my_is_prime
** File description:
** prime nb
*/
#include "my.h"

static int my_square_root_prime(int nb)
{
    int i = 0;

    while (i <= nb){
        if (my_compute_power_rec(i, 2) >= nb){
            return i;
        }
        i++;
    }
    return 0;
}

int my_is_prime(int nb)
{
    int sqr = my_square_root_prime(nb);
    int i = 2;

    if (nb == 2){
        return 1;
    }
    if (nb == 1){
        return 0;
    }
    while (i <= sqr){
        if ((nb % i) == 0){
            return 0;
        }
        i++;
    }
    return 1;
}
