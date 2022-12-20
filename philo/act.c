/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:05:13 by wochae            #+#    #+#             */
/*   Updated: 2022/12/20 15:05:17 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->fork[philo->left]);
	prints(info, philo->id, FORK);
	pthread_mutex_lock(&info->fork[philo->right]);
	prints(info, philo->id, FORK);
	prints(info, philo->id, EAT);
	pthread_mutex_lock(&info->check_last_eat);
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&info->check_last_eat);
	philo->n_eat += 1;
	psleep(info->t_eat);
	pthread_mutex_unlock(&(info->fork[philo->right]));
	pthread_mutex_unlock(&(info->fork[philo->left]));
	philo->status = SLEEP;
}

void	philo_sleep(t_info *info, t_philo *philo)
{
	prints(info, philo->id, SLEEP);
	psleep(info->t_sleep);
	philo->status = THINK;
}

void	philo_think(t_info *info, t_philo *philo)
{
	prints(info, philo->id, THINK);
	philo->status = EAT;
}

void	add_full(t_info *info, int n_eat)
{
	if (n_eat == info->n_must_eat)
	{
		pthread_mutex_lock(&(info->check_full));
		info->n_full_philo += 1;
		pthread_mutex_unlock(&(info->check_full));
	}
}

void	*philo_act(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	if (philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		if ((info->n_must_eat != -1 && philo->n_eat >= info->n_must_eat)
			|| is_dead(info, philo))
			break ;
		if (philo->status == EAT)
			philo_eat(info, philo);
		else if (philo->status == SLEEP)
			philo_sleep(info, philo);
		else if (philo->status == THINK)
			philo_think(info, philo);
	}
	add_full(info, philo->n_eat);
	return (0);
}
