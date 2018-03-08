NAME	= program

CC	= g++

RM	= rm -f

SRCS	= ./srcs/main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./includes/
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
