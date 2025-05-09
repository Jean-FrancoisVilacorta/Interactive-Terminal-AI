##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC =	src/my_getline/my_getline.c					\
	src/my_getline/window/get_data.c				\
	src/my_getline/window/print_info.c				\
	src/my_getline/window/window_data.c				\
	src/my_getline/window/key_enter.c				\
	src/my_getline/window/special_keys.c			\
	src/my_getline/history/get_history.c				\
	src/my_getline/history/replace_file.c				\
	src/my_getline/autocompletion/get_files.c				\
	src/my_getline/autocompletion/modify_auto.c				\
	src/my_getline/autocompletion/autocomplete.c			\
	src/my_getline/autocompletion/search_files.c			\
	src/my_getline/autocompletion/print_autocompletion.c	\
	src/my_getline/autocompletion/change_column.c			\
	src/AI/gpt_demand.c							\
	src/AI/key/verify_key.c							\
	src/AI/key/create_api_key.c						\
	lib/src/my_strlen.c			\
	lib/src/my_str_to_word_array.c	\
	lib/src/my_strcmp.c				\
	lib/src/my_dputstr.c			\
	lib/src/my_strcpy.c				\
	lib/src/my_strstrcpy.c			\
	lib/src/my_getline.c			\
	lib/src/my_realloc.c			\
	lib/src/my_str_cmb.c			\
	lib/src/add_new_line.c			\
	lib/src/open_file.c				\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -g3 -lcurl -lcjson

CPPFLAGS = -iquote ./include/

INCLUDE = -I ./include/

GPT = sudo cp src/AI/exec/gpt.py /bin/

NAME = libgetline.a

MAKE = make

all: make_c

make_c: $(NAME)

$(NAME): $(OBJ)
	sudo $(GPT)
	ar rc $(NAME) $(OBJ)
	mv $(NAME) ../lib/
	cp include/* ../include

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../lib/$(NAME)

re: fclean all

unit_tests: re
	gcc -o unit_tests tests/test.c --coverage -lcriterion
	gcc -o unit_tests tests/test.c --coverage -lcriterion

tests_run:
	./unit_tests

clean_test: fclean
	rm *.gcno ; rm *.gcda ; rm unit_tests
