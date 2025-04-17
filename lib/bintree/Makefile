##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## task01
##

SRC	=	src/btree_apply_infix.c		\
		src/btree_apply_prefix.c	\
		src/btree_apply_suffix.c	\
		src/create_node.c			\
		src/free_bintree.c			\

OBJ	=	$(SRC:.c=.o)

NAME	=	libbintree.a

NAME_H	=	bintree.h

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
