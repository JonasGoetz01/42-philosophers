NAME = philo

SRC := src/

WFLAGS := -Wall -Werror -Wextra

# SRC
SRCCFILES := $(SRC)input.c \
			 $(SRC)log.c \
			 $(SRC)utils.c \
			 $(SRC)utils2.c \
			 $(SRC)philo_create.c \
			 $(SRC)philo_routine.c \
			 $(SRC)time.c \
			 $(SRC)philo_checker.c \
			 $(SRC)philos.c

OFILES := $(SRCCFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	cc $(WFLAGS) $(OFILES) -o $(NAME) 

clean: 
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: helgrind re fclean all clean
