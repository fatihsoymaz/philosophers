NAME = philo

SRCS= main.c philo_init.c philo.c thread.c 
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re: clean all

.PHONY : all clean fclean re 