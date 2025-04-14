/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** main
*/

#include "my_getline.h"



static void simulate_shell(void)
{
    return 0;
}

int main(void)
{
    char path[140];

    if (getcwd(path, sizeof(path)) == NULL)
        return 84;
    my_getline(path);
}
