NAME = philo

SRCS = main.c utils.c philo_control.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@${MAKE} -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@${MAKE} -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re