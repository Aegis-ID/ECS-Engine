##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## A Lib Makefile
##

NAME	=	ecs.so

INCLUDE	=	./include/

SRC		=	$(addprefix src/,	\
			Vector.cpp	\
			Entity.cpp	\
			SystemManager.cpp	\
			)	\

CXX			?=	g++
CPPFLAGS 	= -iquote $(INCLUDE)
CXXFLAGS 	=	-std=c++20 -Wall -Wextra -Werror -fPIC
DEBUG		=	-g3
LDFLAGS		=	-shared

OBJ	=	$(SRC:.cpp=.o)

CP	=	cp

all: $(NAME) clean

$(NAME):	$(OBJ)
			$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)
clean:
		$(RM) $(OBJ)	\
		$(RM) *log

fclean: clean
		$(RM) $(NAME)

re: fclean all

debug:	CXXFLAGS += $(DEBUG)
debug:	$(NAME)

.PHONY: all clean fclean re
