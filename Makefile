##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC = 	main.c						\
		$(addprefix src/,			\
		shell_loop.c				\
		print_signal.c				\
		fill_tree.c					\
		$(addprefix builtin/, 		\
		cd.c						\
		get_env_var.c				\
		env.c						\
		setenv.c					\
		unsetenv.c					\
		alias.c						\
		unalias.c					\
		foreach.c					\
		fg.c              			\
		bg.c              			\
		jobs.c              		\
		repeat.c)					\
		$(addprefix execution/, 	\
		dollars_signe.c				\
		exec_command.c				\
		exec_builtin.c				\
		error_case.c				\
		file_access.c				\
		cmd_type.c					\
    	globbings.c     			\
		is_an_alias.c)				\
		$(addprefix redirector/,	\
		input.c						\
		output.c					\
		pipe.c						\
		error.c)					\
		$(addprefix job_controls/,	\
		jobs_utils.c   				\
		job_state_transition.c   	\
		sanytise_cmd_for_jobs.c))   \

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
