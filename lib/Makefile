SFML		=	libsfml.so

NCURSES		=	libncurses.so

CC		=	g++

RM		=	rm -f

SRCSFML		=	./ncurses/LibNcurses.cpp

SRCNCURSES	=	./sfml/LibSfml.cpp

OBJSFML		=	$(SRCSFML:.cpp=.o)

OBJNCURSES	=	$(SRCNCURSES:.cpp=.o)

CPPFLAGS	=	-I ./includes/
CPPFLAGS	+=	-W -Wall -Wextra

LDFLAGS		=	-shared

all:		$(SFML) $(NCURSES)

$(SFML):	$(OBJSFML)
		$(CC) $(OBJSFML) -o $(SFML) $(LDFLAGS)

$(NCURSES):	$(OBJNCURSES)
		$(CC) $(OBJNCURSES) -o $(NCURSES) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(SFML) $(NCURSES)

re:		fclean all

.PHONY:		all clean fclean re
