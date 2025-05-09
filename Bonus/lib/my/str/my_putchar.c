/*
** EPITECH PROJECT, 2024
** clc
** File description:
** clc
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
