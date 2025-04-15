##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC =	src/main.c	\
	src/shell.c 	\
	src/ouput/analyze_ouput.c	\
	src/ouput/correct_format.c	\
	src/ouput/struct_commands.c	\
	src/free/free.c	\
	src/env/env.c		\
	src/env/setenv.c	\
	src/env/get_path.c	\
	src/env/unsetenv.c	\
	src/env/get_env.c	\
	src/commands/redirect_pipe.c	\
	src/commands/redirect_to_file.c	\
	src/commands/append_to_file.c	\
	src/commands/default_command.c	\
	src/commands/change_directory.c	\
	src/commands/send_file_to_exec.c	\
	src/commands/read_to_exec.c 	\
	src/default_data/default_data.c 	\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -g3

CPPFLAGS = -iquote ./include/

LDFLAGS = -L. -lmy

INCLUDE = -I ./include/

NAME = mysh

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
