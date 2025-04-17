/*
** EPITECH PROJECT, 2025
** lib
** File description:
** header
*/


#ifndef MY_H
    #define MY_H
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define FAIL -1
    #define SUCCESS 0
    #include <unistd.h>
    #include <stdarg.h>



typedef struct dprint_func_s {
    char flag;
    void (*function)(int fd, va_list arg);
}dprint_func_t;

// lib
// dprintf
    #define CHAR_SIZE 1
int my_dprintf(int fd, char *str, ...);
void print_nbr(int fd, va_list arg);
void print_str(int fd, va_list arg);
void print_float(int fd, va_list arg);
void print_char(int fd, va_list arg);

static const dprint_func_t dprint_function[] = {
    {'d', &print_nbr},
    {'i', &print_nbr},
    {'f', &print_float},
    {'s', &print_str},
    {'c', &print_char},
    {FAIL, NULL}};

// nbr
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_getnbr(char const *str);
int is_float(char *str);
int is_nbr(char c);
int is_str_int(char *str);
int my_is_prime(int nb);
int my_put_nbr(int nb);
int rev_nbr(int nb);
int is_alphanum(char c);

//str
void my_putchar(char c);
char *my_revstr(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char *str);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int n);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
int my_putstr(const char *str);

char **my_str_to_word_arr(const char *str, const char *delim);
int my_show_word_array(char *const *tab);
int len_word_arr(char **array);
void free_word_arr(char **arr);
char **cp_word_arr(char **origin);


#endif
