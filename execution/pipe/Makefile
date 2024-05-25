NAME	= pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = pipex_utils.c pipex.c split.c pipex_bonus.c main.c \
	   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re