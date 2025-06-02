NAME = minishell

SRC := $(shell find src -name "*.c")

OBJ := $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

LIBS = -lreadline

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
