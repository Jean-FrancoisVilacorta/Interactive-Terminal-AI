/*
** EPITECH PROJECT, 2024
** strncpy
** File description:
** copy n char
*/
char *my_strncpy(char *dest, char const *src, int n)
{
    int j = 0;

    while (src[j] != '\0' && n != 0){
        dest[j] = src[j];
        j++;
        n = n - 1;
    }
    if (dest[j] != '\0'){
        dest[j] = '\0';
    }
    return dest;
}
