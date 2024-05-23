NAME = minishell

CC = cc

CFLAGS = -lreadline

SRCS = main/main.c utils/utils.c utils/split.c main/minishell.c pwd.c parsing/parsing.c parsing/quotes.c parsing/dollar.c builtins/pwd.c builtins/echo.c utils/lst_utils.c

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