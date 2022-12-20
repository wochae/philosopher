# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 15:25:57 by jabae             #+#    #+#              #
#    Updated: 2022/09/05 15:21:27 by jabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS =	philo_bonus.c \
		init_bonus.c \
		run_bonus.c \
		utils_bonus.c \

OBJS = $(SRCS:%.c=%.o)

FLAGS	= -Wall -Wextra -Werror

all	: $(NAME)

$(NAME)	:	$(OBJS)
		@cc $(FLAGS)  -o $(NAME) $(OBJS)
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