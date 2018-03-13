##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
##
##

NIBBLER		=	lib_arcade_nibbler.so

SNAKE		=	lib_arcade_snake.so

CC		=	g++

RM		=	rm -f

SRCNIBBLER	=	./nibbler/Nibbler.cpp

SRCSNAKE	=	./snake/Snake.cpp

OBJNIBBLER	=	$(SRCNIBBLER:.cpp=.o)

OBJSNAKE	=	$(SRCSNAKE:.cpp=.o)

CPPFLAGS	=	-I ./includes/ -I../lib/includes
CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses

all:		$(NIBBLER) $(SNAKE)

$(NIBBLER):	$(OBJNIBBLER)
		$(CC) $(OBJNIBBLER) -o $(NIBBLER) $(LDFLAGS)

$(SNAKE):	$(OBJSNAKE)
		$(CC) $(OBJSNAKE) -o $(SNAKE) $(LDFLAGS)

clean:
		$(RM) $(OBJSNIBBLER)

fclean: 	clean
		$(RM) $(NIBBLER) $(SNAKE)

re:		fclean all

.PHONY:		all clean fclean re
