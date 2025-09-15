NAME= philo

CC= cc
CFLAGS= -Wall -Wextra -Werror -pthread -fsanitize=thread -g3

INCDIR= includes
SRCDIR= src

SRCS= $(SRCDIR)/main.c $(SRCDIR)/parse.c $(SRCDIR)/init.c $(SRCDIR)/time.c $(SRCDIR)/routine.c $(SRCDIR)/clean.c $(SRCDIR)/monitor.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

	