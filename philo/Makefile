NAME=philo

CC=cc
CFLAGS = -Wall -Wextra -Werror


CFILES = philo_create.c \
		 philo.c \
		 prep.c \
		 philo_routine.c \
		 stop.c \
		 time.c \
		 utils.c \
		 supervisor.c

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f philo

helgrind:
	@valgrind --tool=helgrind -s ./philo 1 800 500 500

re: fclean all