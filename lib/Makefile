SFML		=	lib_arcade_sfml.so

NCURSES		=	lib_arcade_ncurses.so

CC		=	g++

RM		=	rm -f

SRCNCURSES	=	./ncurses/LibNcurses.cpp

SRCSFML		=	./sfml/LibSfml.cpp

OBJSFML		=	$(SRCSFML:.cpp=.o)

OBJNCURSES	=	$(SRCNCURSES:.cpp=.o)

CPPFLAGS	=	-I ./includes/
CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses -lsfml-graphics

all:		$(SFML) $(NCURSES)

$(SFML):	$(OBJSFML)
		$(CC) $(OBJSFML) -o $(SFML) $(LDFLAGS)

$(NCURSES):	$(OBJNCURSES)
		$(CC) $(OBJNCURSES) -o $(NCURSES) $(LDFLAGS)

clean:
		$(RM) $(OBJSFML) $(OBJNCURSES)

fclean: 	clean
		$(RM) $(SFML) $(NCURSES)

re:		fclean all

.PHONY:		all clean fclean re
