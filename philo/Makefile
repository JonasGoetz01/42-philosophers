NAME = philo

SRC := src

WFLAGS := -Wall -Werror -Wextra

# SRC
SRCCFILES := input.c \
			 log.c \
			 utils.c \
			 utils2.c \
			 philo_create.c \
			 philo_routine.c \
			 time.c \
			 philo_checker.c \
			 philos.c

SRCCFILES := $(addprefix $(SRC)/, $(SRCCFILES))

# LIBS
CFILES := $(SRCCFILES)
OFILES := $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	cc $(WFLAGS) $(OFILES) -o $(NAME) 

clean: 
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: helgrind re fclean all clean
