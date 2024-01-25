NAME = philos

SRC_DIR = ./philo/

SRC = $(SRC_DIR)main.c \
	  $(SRC_DIR)init.c \
	  $(SRC_DIR)threads.c \
	  $(SRC_DIR)utils.c \
	  $(SRC_DIR)actions.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re