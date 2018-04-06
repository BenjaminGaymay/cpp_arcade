SFML		=	lib_arcade_sfml.so

NCURSES		=	lib_arcade_ncurses.so

ALLEGRO		=	lib_arcade_allegro.so

OPENGL		=	lib_arcade_opengl.so

CC		=	g++

RM		=	rm -f

SRCNCURSES	=	./ncurses/LibNcurses.cpp

SRCSFML		=	./sfml/LibSfml.cpp

SRCALLEGRO	=	./allegro/LibAllegro.cpp

SRCOPENGL	=	./opengl/LibOpengl.cpp

OBJSFML		=	$(SRCSFML:.cpp=.o)

OBJNCURSES	=	$(SRCNCURSES:.cpp=.o)

OBJALLEGRO	=	$(SRCALLEGRO:.cpp=.o)

OBJOPENGL	=	$(SRCOPENGL:.cpp=.o)

CPPFLAGS	=	-I ./includes/
CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses -lsfml-graphics -lsfml-audio -lallegro -lallegro_primitives -lallegro_font -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_ttf -lGL -lGLU

all:		$(SFML) $(NCURSES) $(ALLEGRO) $(OPENGL)

$(SFML):	$(OBJSFML)
		$(CC) $(OBJSFML) -o $(SFML) $(LDFLAGS)

$(NCURSES):	$(OBJNCURSES)
		$(CC) $(OBJNCURSES) -o $(NCURSES) $(LDFLAGS)

$(ALLEGRO):	$(OBJALLEGRO)
		$(CC) $(OBJALLEGRO) -o $(ALLEGRO) $(LDFLAGS)

$(OPENGL):	$(OBJOPENGL)
		$(CC) $(OBJOPENGL) -o $(OPENGL) $(LDFLAGS)

clean:
		$(RM) $(OBJSFML) $(OBJNCURSES) $(OBJALLEGRO) $(OBJOPENGL)

fclean: 	clean
		$(RM) $(SFML) $(NCURSES) $(ALLEGRO) $(OPENGL)

re:		fclean all

.PHONY:		all clean fclean re
