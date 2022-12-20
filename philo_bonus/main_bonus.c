
#include "philo_bonus.h"

void	error_exit(char *str)
{
	if (str)
		printf("%s\n", str);
	exit(1);
}

void	kill_pids(t_philo **philo, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		kill((*philo)[i].pid, SIGINT);
}

int	set_info(t_info *info, char *argv[])
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->n_philo < 0 || info->t_die < 0 || info->t_eat < 0
		|| info->t_sleep < 0)
		return (1);
	info->t_start = get_time();
	info->is_dead = 0;
	if (argv[5])
	{
		info->n_must_eat = ft_atoi(argv[5]);
		if (info->n_must_eat < 0)
			return (1);
	}
	else
		info->n_must_eat = -1;
	return (0);
}

int	set_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * (info->n_philo));
	if (!(*philo))
		error_exit("philo malloc failed\n");
	i = -1;
	while (++i < info->n_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].t_last_eat = get_time();
		(*philo)[i].n_eat = 0;
		(*philo)[i].status = EAT;
		(*philo)[i].info = info;
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid < 0)
		{
			kill_pids(philo, i);
			return (1);
		}
		if ((*philo)[i].pid == 0)
			philo_start(&(*philo)[i]);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || check_digit(argv))
		error_exit("wrong parameters\n");
	if (set_info(&info, argv))
		error_exit("set_info failed\n");
	if (set_sem(&info))
		error_exit("semaphore failed\n");
	if (set_philo(&info, &philo))
		error_exit("set_philo failed\n");
	free_all(&info, philo);
	return (0);
}
