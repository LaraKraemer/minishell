NAME = minishell

SRC := $(shell find src -name "*.c")
OBJ := $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft
LIBS = -lreadline

# Default rule
all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a $(LIBS) -o $(NAME)

# Compile libft
libft/libft.a:
	$(MAKE) -C libft

# Clean only your object files
clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

# Rebuild everything
re: fclean all

