##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC = 	main.c										\
		$(addprefix src/, builtin/get_env_var.c		\
		builtin/cd.c								\
		builtin/env.c								\
		builtin/setenv.c							\
		builtin/unsetenv.c							\
		builtin/alias.c								\
		builtin/unalias.c							\
		shell_loop.c								\
		execution/exec_command.c					\
		execution/exec_builtin.c					\
		execution/error_case.c						\
		execution/is_an_alias.c						\
		execution/globbings.c						\
		print_signal.c								\
		redirector/input.c							\
		redirector/output.c							\
		redirector/pipe.c							\
		redirector/error.c							\
		fill_tree.c									\
		execution/file_access.c						\
		execution/cmd_type.c)						\

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
