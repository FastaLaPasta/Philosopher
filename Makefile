NAME = philosopher
HEAD = philosopher.h
SRCS = main.c parse.c
			
OBJ = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -o3 -fsanitize=thread

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
bonus: all

re: fclean all

.PHONY: all clean fclean re bonus