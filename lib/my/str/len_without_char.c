/*
** EPITECH PROJECT, 2025
** lib my
** File description:
** len whithout char
*/

int len_without_char(char *str, char c)
{
    int i = 0;
    int len = 0;

    if (!str)
        return 0;
    while (str[i] != '\0') {
        if (str[i] != c)
        len++;
        i++;
    }
    return len;
}
