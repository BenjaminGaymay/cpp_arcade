##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
##
##

NIBBLER		=	lib_arcade_nibbler.so

# NCURSES		=	libncurses.so

CC		=	g++

RM		=	rm -f

SRCNIBBLER	=	./nibbler/Nibbler.cpp

# SRCNCURSES	=	./ncurses/LibNcurses.cpp

OBJNIBBLER	=	$(SRCNIBBLER:.cpp=.o)

# OBJNCURSES	=	$(SRCNCURSES:.cpp=.o)

CPPFLAGS	=	-I ./includes/ -I../lib/includes
CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses

all:		$(NIBBLER) #$(NCURSES)

$(NIBBLER):	$(OBJNIBBLER)
		$(CC) $(OBJNIBBLER) -o $(NIBBLER) $(LDFLAGS)

# $(NCURSES):	$(OBJNCURSES)
# 		$(CC) $(OBJNCURSES) -o $(NCURSES) $(LDFLAGS)

clean:
		$(RM) $(OBJSNIBBLER)

fclean: 	clean
		$(RM) $(NIBBLER) #$(NCURSES)

re:		fclean all

.PHONY:		all clean fclean re
