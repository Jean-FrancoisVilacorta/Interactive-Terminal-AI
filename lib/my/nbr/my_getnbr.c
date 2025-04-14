/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** get number
*/

static void is_neg(int nb, int *ptr2)
{
    if (nb == '-'){
            *ptr2 *= -1;
        }
}

static void add(int nb, int *ptr, int *ptr2, int *ptr3)
{
    *ptr = (*ptr * 10) + (nb -48);
    *ptr2 = *ptr2 + 1;
    *ptr3 = *ptr3 + 1;
}

int my_getnbr(char const *str)
{
    int nb = str[0];
    int i = 0;
    int j = 0;
    int neg = 1;
    int d_nb = 0;

    while (nb != '\0' && d_nb == 0){
        is_neg(nb, &neg);
        while (nb < 58 && nb > 47) {
            add(nb, &d_nb, &i, &j);
            nb = str[i];
        }
        if (j > 10){
            return 0;
        }
        i++;
        nb = str[i];
    }
    return (d_nb * neg);
}
