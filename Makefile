NAME	=	arcade

CC	=	g++ -std=c++17

RM	=	rm -f

SRCS	=	./srcs/Console.cpp	\
		./srcs/main.cpp

OBJS	=	$(SRCS:.cpp=.o)

LDFLAGS =	-ldl

CPPFLAGS =	-I./includes/ -I./lib/ -I./lib/includes -I./games/includes
CPPFLAGS +=	-W -Wall -Wextra

all:	$(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	make -C ./lib/

clean:
	$(RM) $(OBJS)
	make clean -C ./lib/

fclean:	clean
	$(RM) $(NAME)
	make fclean -C ./lib/

re: 	fclean all

.PHONY:	all clean fclean re
