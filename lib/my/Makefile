##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## task01
##

SRC	=	str/my_putchar.c				\
		str/my_putstr.c			 		\
		str/my_revstr.c					\
		str/my_strcapitalize.c			\
		str/my_strcat.c					\
		str/my_strcmp.c					\
		str/my_strcpy.c					\
		str/my_strdup.c					\
		str/my_strlen.c					\
		str/my_strlowcase.c				\
		str/my_strncat.c				\
		str/my_strncmp.c				\
		str/my_strncpy.c				\
		str/my_strstr.c					\
		str/my_strupcase.c				\
		nbr/my_alphanum.c				\
		nbr/my_compute_power_rec.c		\
		nbr/my_compute_square_root.c	\
		nbr/my_getnbr.c					\
		nbr/my_is_float.c				\
		nbr/my_is_nbr.c					\
		nbr/my_is_prime.c				\
		nbr/my_put_nbr.c				\
		nbr/my_rev_nbr.c				\
		array/my_show_word_array.c		\
		array/my_str_to_word_array.c	\
		array/print_array.c				\
		array/my_array_len.c			\
		dprintf/my_dprint.c				\
		dprintf/print_function.c		\


OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

NAME_H	=	my.h

CPPFLAGS	=	-iquote ./include/

CFLAGS	=	 -Wall -Wextra -pedantic


all: $(NAME)

$(NAME):	$(OBJ)
		$(AR) rc $(NAME) $(OBJ)
		mv $(NAME) ../
		cp include/$(NAME_H) ../

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re
