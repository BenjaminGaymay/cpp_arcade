##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
##
##

NIBBLER		=	lib_arcade_nibbler.so

SNAKE		=	lib_arcade_snake.so

PACMAN		=	lib_arcade_pacman.so

CC		=	g++

RM		=	rm -f

SRCNIBBLER	=	./nibbler/Nibbler.cpp

SRCSNAKE	=	./snake/Snake.cpp

SRCPACMAN	=	./pacman/Pacman.cpp	\
			./pacman/Ghost.cpp

OBJNIBBLER	=	$(SRCNIBBLER:.cpp=.o)

OBJSNAKE	=	$(SRCSNAKE:.cpp=.o)

OBJPACMAN	=	$(SRCPACMAN:.cpp=.o)

CPPFLAGS	=	-I ./includes/ -I../lib/includes
CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses

all:		$(NIBBLER) $(SNAKE) $(PACMAN)

$(NIBBLER):	$(OBJNIBBLER)
		$(CC) $(OBJNIBBLER) -o $(NIBBLER) $(LDFLAGS)

$(SNAKE):	$(OBJSNAKE)
		$(CC) $(OBJSNAKE) -o $(SNAKE) $(LDFLAGS)

$(PACMAN):	$(OBJPACMAN)
		$(CC) $(OBJPACMAN) -o $(PACMAN) $(LDFLAGS)

clean:
		$(RM) $(OBJNIBBLER) $(OBJSNAKE) $(OBJPACMAN)

fclean: 	clean
		$(RM) $(NIBBLER) $(SNAKE) $(PACMAN)

re:		fclean all

.PHONY:		all clean fclean re
