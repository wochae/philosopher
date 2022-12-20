
#include "philo_bonus.h"

void	philo_eat(t_info *info, t_philo *philo)
{
	sem_wait(info->fork);
	prints(info, philo->id, FORK);
	sem_wait(info->fork);
	prints(info, philo->id, FORK);
	prints(info, philo->id, EAT);
	philo->t_last_eat = get_time();
	philo->n_eat += 1;
	psleep(info->t_eat);
	sem_post(info->fork);
	sem_post(info->fork);
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

// void	add_full(t_info *info, int n_eat)
// {
// 	if (n_eat == info->n_must_eat)
// 	{
// 		pthread_mutex_lock(&(info->check_full));
// 		info->n_full_philo += 1;
// 		pthread_mutex_unlock(&(info->check_full));
// 	}
// }

void	*philo_act(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		if (info->n_must_eat != -1 && philo->n_eat >= info->n_must_eat)
			break ;
		if (philo->status == EAT)
			philo_eat(info, philo);
		else if (philo->status == SLEEP)
			philo_sleep(info, philo);
		else if (philo->status == THINK)
			philo_think(info, philo);
	}
}