##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC = 	main.c							\
		src/builtin/get_env_var.c		\
		src/builtin/cd.c				\
		src/builtin/env.c				\
		src/builtin/setenv.c			\
		src/builtin/unsetenv.c			\
		src/shell_loop.c				\
		src/execution/exec_command.c	\
		src/execution/exec_builtin.c	\
		src/print_signal.c				\
		src/redirector/input.c			\
		src/redirector/output.c			\
		src/redirector/pipe.c			\
		src/redirector/error.c			\
		src/fill_tree.c					\

OBJ = $(SRC:.c=.o)

CPPFLAGS = -iquote ./include/ -iquote ./lib/

CFLAGS = -Wall -Wextra

LDLIBS = -lmy -lbintree

LDFLAGS = -L lib/

VALGRIND_FLAG	= --track-origins=yes --leak-check=full --show-leak-kinds=all

NAME = mysh

all:	build_lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)  $(CFLAGS) $(LDFLAGS) $(LDLIBS)

build_lib:
	$(MAKE) -C lib/my
	$(MAKE) -C lib/bintree

valgrind: build_lib $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -g
	valgrind $(VALGRIND_FLAG) ./$(NAME)

clean:
	$(MAKE) -C lib/my clean
	$(MAKE) -C lib/bintree clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C lib/my fclean
	$(MAKE) -C lib/bintree fclean
	$(RM) $(NAME)

re: fclean all
