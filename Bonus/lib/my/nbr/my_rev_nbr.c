/*
** EPITECH PROJECT, 2025
** lib
** File description:
** rev nbr
*/

#include <stdio.h>

int rev_nbr(int nb)
{
    int result = 0;
    int is_neg = 1;

    if (nb < 0){
        is_neg = -1;
        nb = -nb;
    }
    while (nb > 0){
        result = result * 10 + (nb % 10);
        nb /= 10;
    }
    return result * is_neg;
}
