# 42-friendly Makefile: simple rules, no bonus targets that break norm
NAME = app
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include
SRCS = src/main.c src/project.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
