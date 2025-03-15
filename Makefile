CFILES = philo.c main.c utils.c init.c error_check.c

OFILES = $(CFILES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
