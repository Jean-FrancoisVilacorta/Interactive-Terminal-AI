##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC = 	main.c						\
		getline/src/my_getline/my_getline.c					\
		getline/src/my_getline/window/get_data.c				\
		getline/src/my_getline/window/print_info.c				\
		getline/src/my_getline/window/window_data.c				\
		getline/src/my_getline/window/key_enter.c				\
		getline/src/my_getline/window/special_keys.c			\
		getline/src/my_getline/history/get_history.c				\
		getline/src/my_getline/history/replace_file.c				\
		getline/src/my_getline/autocompletion/get_files.c				\
		getline/src/my_getline/autocompletion/modify_auto.c				\
		getline/src/my_getline/autocompletion/autocomplete.c			\
		getline/src/my_getline/autocompletion/search_files.c			\
		getline/src/my_getline/autocompletion/print_autocompletion.c	\
		getline/src/my_getline/autocompletion/change_column.c			\
		getline/src/AI/gpt_demand.c							\
		getline/src/AI/key/verify_key.c							\
		getline/src/AI/key/create_api_key.c						\
		getline/lib/src/my_strlen.c			\
		getline/lib/src/my_str_to_word_array.c	\
		getline/lib/src/my_strcmp.c				\
		getline/lib/src/my_dputstr.c			\
		getline/lib/src/my_strcpy.c				\
		getline/lib/src/my_strstrcpy.c			\
		getline/lib/src/my_getline.c			\
		getline/lib/src/my_realloc.c			\
		getline/lib/src/my_str_cmb.c			\
		getline/lib/src/add_new_line.c			\
		getline/lib/src/open_file.c				\
		$(addprefix src/,			\
		shell_loop.c				\
		print_signal.c				\
		fill_tree.c					\
		$(addprefix inhibitors/,	\
		have_inhibitor.c			\
		split_inhibitors.c)			\
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
		repeat.c					\
		which.c						\
		where.c)					\
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
		error.c 					\
		parenthese.c)				\
		$(addprefix job_controls/,	\
		jobs_utils.c   				\
		job_state_transition.c   	\
		sanytise_cmd_for_jobs.c))   \

OBJ = $(SRC:.c=.o)

CPPFLAGS = -iquote ./include/ -iquote ./lib/

CFLAGS = -Wall -Wextra

LDLIBS = -lmy -lbintree

LDFLAGS = -L lib/

VALGRIND_FLAG	= --track-origins=yes  --show-leak-kinds=all

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
