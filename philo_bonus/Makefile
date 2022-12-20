# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 15:54:39 by wochae            #+#    #+#              #
#    Updated: 2022/12/20 16:03:32 by wochae           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS =	philo_bonus.c \
		init_bonus.c \
		run_bonus.c \
		utils_bonus.c \

OBJS = $(SRCS:%.c=%.o)

CFLAGS	= -Wall -Wextra -Werror

all	: $(NAME)

$(NAME)	:	$(OBJS)
		@cc $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "🍽 MAKE bonus SUCCESS"

%.o	:	%.c
	@cc $(FLAGS) -c $^ -I./

clean	:
		@rm -f $(OBJS)
		@echo "🍽 CLEAN bonus SUCCESS"

fclean	: 	clean
		@rm -f $(NAME)
		@echo "🍽 FCLEAN bonus SUCCESS"

re : fclean all

.PHONY	: all clean fclean re
