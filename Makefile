##
## EPITECH PROJECT, 2026
## makefile
## File description:
## project
##

SRC     =   src/main.cpp \
			src/NanoTekSpice.cpp \
			src/ComponentFactory.cpp \
			src/components/AComponent.cpp \
			src/components/Link.cpp \
			src/components/elementary_components/AndComponent.cpp \
			src/components/elementary_components/OrComponent.cpp \
			src/components/elementary_components/XorComponent.cpp \
			src/components/elementary_components/NotComponent.cpp \
			src/components/special_components/FalseComponent.cpp \
			src/components/special_components/TrueComponent.cpp \
			src/components/special_components/InputComponent.cpp \
			src/components/special_components/OutputComponent.cpp \
			src/components/special_components/ClockComponent.cpp \
			src/components/gate_components/4001Component.cpp \
			src/components/bonus_components/NorComponent.cpp \
			src/components/bonus_components/NandComponent.cpp

CXX     =   clang++

OBJ     =   $(SRC:.cpp=.o)

NAME    =   nanotekspice

CXXFLAGS = -Wextra -Wall -I ./include/ -I ./include/components -I ./include/components/special_components -I ./include/components/elementary_components -I ./include/components/gate_components -I ./include/components/bonus_components  -std=c++20

LDLIBS   = -lm

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all