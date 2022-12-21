/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:54:44 by wochae            #+#    #+#             */
/*   Updated: 2022/12/21 17:39:39 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_process(t_info *info, t_philo *philo)
{
	sem_close(info->fork);
	sem_close(info->print);
	sem_close(info->check_last_eat);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("check_last_eat");
	free(philo);
	free(info->pid);
}

void	wait_process(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->num_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_pids(info, info->num_philo);
			usleep(2000);
			sem_post(info->print);
			sem_post(info->check_last_eat);
			break ;
		}
		sem_post(info->print);
		sem_post(info->check_last_eat);
	}
}

static int	get_info(char **argv, t_info *info)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (info->num_philo < 1 || info->time_die < 1 || \
		info->time_eat < 1 || info->time_sleep < 1)
		return (1);
	if (argv[5])
	{
		info->num_must_eat = ft_atoi(argv[5]);
		if (info->num_must_eat < 1)
			return (1);
	}
	else
		info->num_must_eat = -1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || get_info(argv, &info))
		ft_error("Invalid Arguments");
	if (init_info(&info))
		ft_error("Semaphore open failed");
	if (init_philo(&info, &philo))
		ft_error("Philo init failed");
	if (init_process(&info, philo))
		ft_error("Philo process failed");
	wait_process(&info);
	free_process(&info, philo);
	return (0);
}
