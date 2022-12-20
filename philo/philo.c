/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:05:37 by wochae            #+#    #+#             */
/*   Updated: 2022/12/20 15:05:38 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	morintoring(t_info *info, t_philo **philo)
{
	int	i;

	i = -1;
	while (1)
	{
		if (++i >= info->n_philo)
			i = 0;
		if (is_dead(info, &(*philo)[i]))
			break ;
		if (is_full(info))
		{
			printf("everyone is full!\n");
			break ;
		}
	}
}

int	is_dead(t_info *info, t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&(info->check_death));
	dead = info->is_dead;
	pthread_mutex_unlock(&(info->check_death));
	if (dead)
		return (dead);
	pthread_mutex_lock(&(info->check_last_eat));
	if (info->t_die < get_time() - philo->t_last_eat)
		dead = 1;
	pthread_mutex_unlock(&(info->check_last_eat));
	if (dead)
	{
		prints(info, philo->id, DIE);
		pthread_mutex_lock(&(info->check_death));
		info->is_dead = dead;
		pthread_mutex_unlock(&(info->check_death));
	}
	return (dead);
}

int	is_full(t_info *info)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&(info->check_full));
	if (info->n_full_philo >= info->n_philo)
		full = 1;
	pthread_mutex_unlock(&(info->check_full));
	return (full);
}

int	philo_start(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		philo[i].t_last_eat = get_time();
		if (pthread_create(&philo[i].thread, 0, philo_act, &philo[i]))
			return (1);
	}
	return (0);
}
