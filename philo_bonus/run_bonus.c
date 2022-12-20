/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:54:50 by wochae            #+#    #+#             */
/*   Updated: 2022/12/20 15:54:50 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat_philo(t_info *info, t_philo *philo)
{
	sem_wait(info->fork);
	print_philo(info, philo->id, FORK);
	sem_wait(info->fork);
	print_philo(info, philo->id, FORK);
	print_philo(info, philo->id, EAT);
	philo->num_eat += 1;
	sem_wait(info->check_last_eat);
	philo->time_last_eat = init_time();
	sem_post(info->check_last_eat);
	wait_time(info->time_eat);
	sem_post(info->fork);
	sem_post(info->fork);
}

static void	*monitoring(void	*ph)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ph;
	info = philo->info;
	while (1)
	{
		sem_wait(info->check_last_eat);
		if ((long long)info->time_die < init_time() - philo->time_last_eat)
		{
			sem_post(info->check_last_eat);
			print_philo(info, philo->id, DIE);
			exit(EXIT_FAILURE);
		}
		sem_post(info->check_last_eat);
		usleep(200);
	}
	return (0);
}

void	*run_philo(t_info *info, t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &monitoring, philo) != 0)
		exit (EXIT_FAILURE);
	pthread_detach(philo->thread);
	if (!(philo->id % 2))
		wait_time(info->time_eat * 0.5);
	while (1)
	{
		eat_philo(info, philo);
		if (philo->num_eat == info->num_must_eat)
			break ;
		print_philo(info, philo->id, SLEEP);
		wait_time(info->time_sleep);
		print_philo(info, philo->id, THINK);
	}
	exit (EXIT_SUCCESS);
}
