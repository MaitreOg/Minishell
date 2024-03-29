NAME = minishell

CC = cc

CFLAGS = -lreadline

SRCS = main.c utils.c split.c minishell.c pwd.c parsing.c

OBJECTS = $(SRCS:.c=.o) 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus re