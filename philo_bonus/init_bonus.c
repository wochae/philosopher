/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:54:36 by wochae            #+#    #+#             */
/*   Updated: 2022/12/20 15:54:37 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	init_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
		return (printf("[Error] Can't get time\n"));
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

int	init_info(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("check_last_eat");
	info->time_start = init_time();
	info->fork = sem_open("fork", O_CREAT, 0644, info->num_philo);
	if (info->fork == SEM_FAILED)
		return (-1);
	info->print = sem_open("print", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		return (-1);
	info->check_last_eat = sem_open("check_last_eat", O_CREAT, 0644, 1);
	if (info->check_last_eat == SEM_FAILED)
		return (-1);
	return (0);
}

int	init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->num_philo);
	if (!philo)
		return (-1);
	i = -1;
	while (++i < info->num_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].num_eat = 0;
		(*philo)[i].info = info;
		(*philo)[i].time_last_eat = init_time();
	}
	return (0);
}

int	init_process(t_info *info, t_philo *philo)
{
	int	i;

	info->pid = malloc(sizeof(pid_t) * info->num_philo);
	if (!info->pid)
		return (-1);
	i = -1;
	while (++i < info->num_philo)
	{
		info->pid[i] = fork();
		if (info->pid[i] < 0)
		{
			kill_pids(info, i);
			return (-1);
		}
		if (info->pid[i] == 0)
			run_philo(info, &philo[i]);
	}
	return (0);
}
