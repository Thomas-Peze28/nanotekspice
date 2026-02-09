##
## EPITECH PROJECT, 2026
## makefile
## File description:
## project
##

SRC	=	src/main.c	\
		src/NanoTekspice.cpp	\

OBJ	=	$(SRC:.c=.o)

NAME	=	nanotekspice

CFLAGS = -Wextra -Wall -I ./include/ -lm -std=gnu17

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) $(CFLAGS) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all
