/*
** EPITECH PROJECT, 2024
** check_nbr
** File description:
** verify if nbr or ltr
*/

int is_alphanum(char c)
{
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')){
        return 1;
    }
    return 0;
}
