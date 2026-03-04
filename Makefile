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

ADVANCED_COMPONENTS = src/components/advanced_components/4008Component.cpp \
					  src/components/advanced_components/LoggerComponent.cpp \
					  src/components/advanced_components/4512Component.cpp \
					  src/components/advanced_components/4514Component.cpp \

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
			$(ADVANCED_COMPONENTS) \
			$(BONUS_COMPONENTS) \

SRC_TESTS = tests/tests_4001.cpp	\
			tests/tests_4008.cpp	\
			tests/tests_4011.cpp	\
			tests/tests_4030.cpp	\
			tests/tests_4069.cpp	\
			tests/tests_4071.cpp	\
			tests/tests_4081.cpp	\
			tests/tests_and.cpp	\
			tests/tests_circuit.cpp	\
			tests/tests_clock.cpp	\
			tests/tests_components.cpp	\
			tests/tests_factory.cpp	\
			tests/tests_false.cpp	\
			tests/tests_input.cpp	\
			tests/tests_nand.cpp	\
			tests/tests_nor.cpp	\
			tests/tests_not.cpp	\
			tests/tests_or.cpp	\
			tests/tests_output.cpp	\
			tests/tests_parsing.cpp	\
			tests/tests_true.cpp	\
			tests/tests_xor.cpp

SRC_NO_MAIN = $(filter-out src/main.cpp, $(SRC))

OBJ_TESTS = $(SRC_NO_MAIN:.cpp=.gcda)

CXX     =   clang++

OBJ     =   $(SRC:.cpp=.o)

NAME    =   nanotekspice

NAME_TESTS = unit_tests

CXXFLAGS = -Wextra -Wall -I ./include/ -I ./include/components -I ./include/components/special_components -I ./include/components/elementary_components -I ./include/components/gate_components -I ./include/components/advanced_components -I ./include/components/bonus_components -I ./include/parsing -std=c++20

TESTS_CXXFLAGS = $(CXXFLAGS) --coverage

TESTS_LDFLAGS = -lcriterion --coverage

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

tests_run:
	@printf "$(CYAN)[TESTS]$(RESET) Compiling unit tests with coverage...\n"
	@$(CXX) $(TESTS_CXXFLAGS) $(SRC_NO_MAIN) $(SRC_TESTS) $(TESTS_LDFLAGS) -o $(NAME_TESTS)
	@printf "$(GREEN)[OK]$(RESET) Tests binary $(CYAN)'$(NAME_TESTS)'$(RESET) compiled successfully.\n\n"
	@printf "$(CYAN)[TESTS]$(RESET) Running tests...\n"
	@./$(NAME_TESTS)
	@$(MAKE) --no-print-directory clean_tests

clean_tests:
	@rm -f *.gcda *.gcno *.o
	@rm -f $(NAME_TESTS)
	@printf "$(YELLOW)[INFO]$(RESET) Test artifacts removed.\n"

.PHONY: all clean fclean re tests_run clean_tests