NAME = philosopher
HEAD = philosopher.h
SRCS = main.c ft_atoi.c
			
OBJ = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(CPPFLAGS) $(LIB) -lreadline -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
bonus: all

re: fclean all