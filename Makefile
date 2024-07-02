NAME = minishell

CC = cc

#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g

LDFLAGS = -lreadline

SRCS =	main/main.c main/minishell.c \
		utils/utils.c utils/split.c utils/lst_utils.c \
		utils/get_next_line/get_next_line.c utils/free.c \
		utils/get_next_line/get_next_line_utils.c utils/error.c \
		parsing/parsing.c parsing/quotes.c parsing/dollar.c \
		builtins/pwd.c builtins/echo.c  builtins/cd.c builtins/export.c \
		builtins/unset.c builtins/env.c utils/ft_itoa.c \
		execution/execution.c execution/redirection.c execution/compute.c \
		execution/pipe.c builtins/utils_builtins.c

OBJECTS = $(SRCS:.c=.o) 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus re