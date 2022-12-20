
#include "philo_bonus.h"

sem_t	*get_sem(char *label, int num)
{
	sem_t *sem;

	sem = sem_open(label, O_CREAT | O_EXCL, 0644, (unsigned int)num);
	if (sem == SEM_FAILED)
	{
		sem_unlink(label);
		sem = sem_open(label, O_CREAT | O_EXCL, 0644, (unsigned int)num);
	}
	return (sem);
}

int set_sem(t_info *info)
{
	info->fork = get_sem("fork", info->n_philo);
	if (info->fork == SEM_FAILED)
		return (1);
	info->print = get_sem("print", 1);
	if (info->print == SEM_FAILED)
		return (1);
	info->check_death = get_sem("check_death", 1);
	if (info->check_death == SEM_FAILED)
		return (1);
	info->check_full = get_sem("check_full", 1);
	if (info->check_full == SEM_FAILED)
		return (1);
	return (0);
}

int	free_all(t_info *info, t_philo *philos)
{
	int	i;

	i = -1;
	// while (++i < info->n_philo)
	// 	kill(philos[i].pid, SIGTERM);
	sem_close(info->fork);
	sem_unlink("fork");
	sem_close(info->print);
	sem_unlink("print");
	sem_close(info->check_death);
	sem_unlink("check_death");
	sem_close(info->check_full);
	sem_unlink("check_full");
	free(philos);
	return (0);
}
