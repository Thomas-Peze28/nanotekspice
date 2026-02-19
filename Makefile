##
## EPITECH PROJECT, 2026
## makefile
## File description:
## project
##

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
RESET=\033[0m

ELEMENTARY_COMPONENTS = src/components/elementary_components/AndComponent.cpp \
						src/components/elementary_components/OrComponent.cpp \
						src/components/elementary_components/XorComponent.cpp \
						src/components/elementary_components/NotComponent.cpp \

SPECIAL_COMPONENTS = src/components/special_components/FalseComponent.cpp \
					 src/components/special_components/TrueComponent.cpp \
					 src/components/special_components/InputComponent.cpp \
					 src/components/special_components/OutputComponent.cpp \
					 src/components/special_components/ClockComponent.cpp \

GATE_COMPONENTS = src/components/gate_components/4001Component.cpp \
				  src/components/gate_components/4011Component.cpp \
				  src/components/gate_components/4030Component.cpp \
				  src/components/gate_components/4069Component.cpp \
				  src/components/gate_components/4071Component.cpp \
				  src/components/gate_components/4081Component.cpp \

BONUS_COMPONENTS = src/components/bonus_components/NorComponent.cpp \
				   src/components/bonus_components/NandComponent.cpp \

SRC     =   src/main.cpp \
			src/NanoTekSpice.cpp \
			src/Circuit.cpp \
			src/ComponentFactory.cpp \
			src/components/AComponent.cpp \
			src/components/Link.cpp \
			src/parsing/Parsing.cpp	\
			$(ELEMENTARY_COMPONENTS) \
			$(SPECIAL_COMPONENTS) \
			$(GATE_COMPONENTS) \
			$(BONUS_COMPONENTS) \

CXX     =   clang++

OBJ     =   $(SRC:.cpp=.o)

NAME    =   nanotekspice

CXXFLAGS = -Wextra -Wall -I ./include/ -I ./include/components -I ./include/components/special_components -I ./include/components/elementary_components -I ./include/components/gate_components -I ./include/components/bonus_components -I ./include/parsing -std=c++20

LDLIBS   = -lm

.SILENT:

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDLIBS)
	@printf "$(GREEN)[OK]$(RESET) Binary $(CYAN)'$(NAME)'$(RESET) compiled successfully.\n"

clean:
	rm -f $(OBJ)
	@printf "$(YELLOW)[INFO]$(RESET) Object files removed.\n"

fclean: clean
	rm -f $(NAME)
	@printf "$(YELLOW)[INFO]$(RESET) Binary $(CYAN)'$(NAME)'$(RESET) removed.\n"

re:     fclean all
		@printf "$(BLUE)[INFO]$(RESET) Project rebuilt successfully.\n"