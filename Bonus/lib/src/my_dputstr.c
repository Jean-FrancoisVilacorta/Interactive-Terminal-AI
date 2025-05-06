/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** display one by one, the characters of a string
*/

#include <unistd.h>

static int my_strlen(char const *str)
{
    int count = 0;

    if (str == NULL)
        return 0;
    while (str[count] != '\0')
        count++;
    return count;
}

int my_dputstr(int const nb, char const *str)
{
    int count = my_strlen(str);
    int ret = 0;

    ret = write(nb, str, count);
    return ret;
}
