/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:05:46 by wochae            #+#    #+#             */
/*   Updated: 2022/12/21 18:36:46 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prints(t_info *info, int id, int status)
{
	long long	now;
	int			dead;

	pthread_mutex_lock(&(info->check_death));
	dead = info->is_dead;
	if (!dead)
	{
		pthread_mutex_lock(&(info->print));
		now = get_time() - info->t_start;
		if (status == 1)
			printf("%lld %d has taken a fork\n", now, id);
		else if (status == 2)
			printf("%lld %d is eating\n", now, id);
		else if (status == 3)
			printf("%lld %d is sleeping\n", now, id);
		else if (status == 4)
			printf("%lld %d is thinking\n", now, id);
		else if (status == 5)
			printf("%lld %d died\n", now, id);
		pthread_mutex_unlock(&(info->print));
	}
	pthread_mutex_unlock(&(info->check_death));
}

void	psleep(long long t_sleep)
{
	long long	t_start;
	long long	t_now;

	t_start = get_time();
	while (1)
	{
		t_now = get_time();
		if (t_now - t_start >= t_sleep)
			break ;
		usleep(100);
	}
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0) == -1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_digit(char *argv[])
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			c = argv[i][j];
			if (!(c >= '0' && c <= '9') && c != '+')
				return (1);
			if (c == '+' && !(argv[i][j + 1] >= '0' && argv[i][j + 1] <= '9'))
				return (1);
			if (c == '+' && j != 0)
				return (1);
		}
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	ret;

	sign = 1;
	ret = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str && ((*str == '-') || (*str == '+')))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= 48 && *str <= 57)
	{
		ret = ret * 10 + (*str - 48);
		if (ret * sign > 2147483647)
			return (-1);
		else if (ret * sign < -2147483648)
			return (0);
		str++;
	}
	return (ret * sign);
}
