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
		src/builtin/alias.c				\
		src/builtin/unalias.c			\
		src/shell_loop.c				\
		src/execution/exec_command.c	\
		src/execution/exec_builtin.c	\
		src/execution/error_case.c		\
		src/execution/is_an_alias.c		\
		src/print_signal.c				\
		src/redirector/input.c			\
		src/redirector/output.c			\
		src/redirector/pipe.c			\
		src/redirector/error.c			\
		src/fill_tree.c					\
		src/execution/file_access.c		\
		src/execution/cmd_type.c		\

OBJ = $(SRC:.c=.o)

CPPFLAGS = -iquote ./include/ -iquote ./lib/

CFLAGS = -Wall -Wextra

LDLIBS = -lmy -lbintree

LDFLAGS = -L lib/

VALGRIND_FLAG	= --track-origins=yes --leak-check=full --show-leak-kinds=all

NAME = 42sh

all:	build_lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)  $(CFLAGS) $(LDFLAGS) $(LDLIBS)

build_lib:
	$(MAKE) -C lib/my
	$(MAKE) -C lib/bintree

valgrind: build_lib $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -g
	valgrind $(VALGRIND_FLAG) ./$(NAME)

debug: CPPFLAGS += -g3
debug: all

clean:
	$(MAKE) -C lib/my clean
	$(MAKE) -C lib/bintree clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C lib/my fclean
	$(MAKE) -C lib/bintree fclean
	$(RM) $(NAME)

re: fclean all debug
