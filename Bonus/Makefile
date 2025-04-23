##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC =	src/main.c 							\
	src/my_getline/get_data.c				\
	src/my_getline/print_info.c				\
	src/my_getline/my_getline.c				\
	src/my_getline/special_keys.c			\
	src/my_getline/window/window_data.c			\
	src/my_getline/history/get_history.c			\
	src/my_getline/autocompletion/get_files.c				\
	src/my_getline/autocompletion/modify_auto.c				\
	src/my_getline/autocompletion/autocomplete.c			\
	src/my_getline/autocompletion/search_files.c			\
	src/my_getline/autocompletion/print_autocompletion.c	\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -g3

CPPFLAGS = -iquote ./include/

LDFLAGS = -L. -lmy

INCLUDE = -I ./include/

NAME = 42zh

MAKE = make

all: clib make_c

clib:
	 cd lib ; make re; cd ..

make_c: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	cd lib/ ; make clean ; cd ..

fclean: clean
	rm -f $(NAME)
	cd lib/ ; make fclean ; cd ..

re: fclean all

unit_tests: re
	gcc -o unit_tests tests/test.c --coverage -lcriterion
	gcc -o unit_tests tests/test.c --coverage -lcriterion

tests_run:
	./unit_tests

clean_test: fclean
	rm *.gcno ; rm *.gcda ; rm unit_tests
