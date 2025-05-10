##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## A Lib Makefile
##

NAME	=	ecs

SRC		=	$(addprefix src/,	\
			ECS/Entity.cpp	\
			ECS/EntityManager.cpp	\
			ECS/SystemManager.cpp	\
			Utils/Logger.cpp	\
			)	\

CXX			?=	g++
CPPFLAGS 	= -I include/
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
