/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** compare 2 str
*/

int my_strcmp(char const *s1, char const *s2)
{
    int result = 0;
    int i = 0;

    if (!s1 || !s2)
        return -1;
    for (i = 0; (s1[i] != '\0' && s2[i] != '\0') && (s1[i] == s2[i]); i++);
    result = s1[i] - s2[i];
    return result;
}
