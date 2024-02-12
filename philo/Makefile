NAME = philos

SRC := src

WFLAGS := -Wall -Werror -Wextra

# SRC
SRCCFILES := input.c \
			 log.c \
			 utils.c \
			 philo_create.c \
			 philo_runtime.c \
			 time.c \
			 philo_checker.c \
			 philos.c

SRCCFILES := $(addprefix $(SRC)/, $(SRCCFILES))

# LIBS
CFILES := $(SRCCFILES)
OFILES := $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	gcc $(WFLAGS) $(OFILES) -o $(NAME) 

clean: 
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)
	rm -f philosophers

re: fclean all

