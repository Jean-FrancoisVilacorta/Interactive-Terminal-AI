/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** print an number
*/

#include <unistd.h>
#include "my.h"

int my_put_nbr(int nb)
{
    if (nb < -2147483647 || nb > 2147483647) {
        return 0;
    }
    if (nb < 0) {
        nb = -nb;
        my_putchar('-');
    }
    while (nb > 0){
        my_putchar('0' + (nb % 10));
        nb /= 10;
    }
    return 1;
}
