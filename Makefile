##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## A Lib Makefile
##

NAME	=	ecs

INCLUDE	=	./include/

SRC		=	$(addprefix src/,	\
			EntityManager.cpp	\
			SystemManager.cpp	\
			)	\

CXX			?=	g++
CPPFLAGS 	= -iquote $(INCLUDE)
CXXFLAGS 	=	-std=c++20 -Wall -Wextra -Werror -fPIC

LDFLAGS		=	-shared

OBJ	=	$(SRC:.cpp=.o)

shared:	$(OBJ)
		$(CXX) $(LDFLAGS) -o $(NAME).so $(OBJ)

static: $(OBJ)
		$(AR) rcs $(NAME).a $(OBJ)

clean:
		$(RM) $(OBJ)	\
		$(RM) *log

fclean: clean
		$(RM) $(NAME).a	\
		$(RM) $(NAME).so	\

.PHONY: static shared clean fclean
