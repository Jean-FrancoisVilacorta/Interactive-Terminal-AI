##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC = src/my_strlen.c			\
	src/my_str_to_word_array.c	\
	src/my_strcmp.c				\
	src/my_dputstr.c			\
	src/my_strcpy.c				\
	src/my_strstrcpy.c			\
	src/my_getline.c			\
	src/my_realloc.c			\
	src/my_str_cmb.c			\

OBJ = $(SRC:.c=.o)

CPPFLAGS = -iquote ./include/

INCLUDE = -I ./include/

CFLAGS = -Wall -Wextra -g3

LDLIBS = -lm -lmy

NAME = libmy.a

MAKE = make

all:	$(NAME)

clib:
	$(MAKE) -C lib/my/

$(NAME): $(OBJ)
	cp include/lib.h ../include/
	ar rc $(NAME) $(OBJ); mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME) ../include/lib.h

re: fclean all
