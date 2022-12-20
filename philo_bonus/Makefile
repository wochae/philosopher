
NAME =  philo_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main_bonus.c philo_bonus.c utils_bonus.c sem_bonus.c act_bonus.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

%.o :%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
