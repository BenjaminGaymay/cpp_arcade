SFML		=	lib_arcade_sfml.so

NCURSES		=	lib_arcade_ncurses.so

ALLEGRO		=	lib_arcade_allegro.so

CC		=	g++

RM		=	rm -f

SRCNCURSES	=	./ncurses/LibNcurses.cpp

SRCSFML		=	./sfml/LibSfml.cpp

SRCALLEGRO	=	./allegro/LibAllegro.cpp

OBJSFML		=	$(SRCSFML:.cpp=.o)

OBJNCURSES	=	$(SRCNCURSES:.cpp=.o)

OBJALLEGRO	=	$(SRCALLEGRO:.cpp=.o)

CPPFLAGS	=	-I ./includes/
CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses -lsfml-graphics -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf

all:		$(SFML) $(NCURSES) $(ALLEGRO)

$(SFML):	$(OBJSFML)
		$(CC) $(OBJSFML) -o $(SFML) $(LDFLAGS)

$(NCURSES):	$(OBJNCURSES)
		$(CC) $(OBJNCURSES) -o $(NCURSES) $(LDFLAGS)

$(ALLEGRO):	$(OBJALLEGRO)
		$(CC) $(OBJALLEGRO) -o $(ALLEGRO) $(LDFLAGS)

clean:
		$(RM) $(OBJSFML) $(OBJNCURSES) $(OBJALLEGRO)

fclean: 	clean
		$(RM) $(SFML) $(NCURSES) $(ALLEGRO)

re:		fclean all

.PHONY:		all clean fclean re
