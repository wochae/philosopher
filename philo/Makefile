# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 15:05:30 by wochae            #+#    #+#              #
#    Updated: 2022/12/21 16:56:57 by wochae           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c philo.c act.c utils.c

CC = cc
CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		@cc $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "🍽 MAKE SUCCESS"

%.o :%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean	:
		@rm -rf $(OBJS)
		@echo "🍽 CLEAN SUCCESS"

fclean	:	clean
		@rm -rf $(NAME)
		@echo "🍽 FCLEAN SUCCESS"

re : fclean all

.PHONY: all clean fclean re
