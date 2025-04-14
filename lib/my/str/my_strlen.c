/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** length of a stt
*/
int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len]){
        len++;
    }
    return len;
}
