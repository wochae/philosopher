/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:54:47 by wochae            #+#    #+#             */
/*   Updated: 2022/12/20 15:54:48 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_info
{
	pid_t			*pid;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	long long		time_start;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*check_last_eat;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				num_eat;
	long long		time_last_eat;
	pthread_t		thread;
	t_info			*info;
}	t_philo;

/* init */
int				init_info(t_info *info);
int				init_philo(t_info *info, t_philo **philo);
int				init_process(t_info *info, t_philo *philo);
long long		init_time(void);

/* run */
void			*run_philo(t_info *info, t_philo *philo);

/* utils */
void			ft_error(char *message);
void			kill_pids(t_info *info, int id);
void			print_philo(t_info *info, int id, int status);
int				check_end(t_info *info, t_philo *philo, int i);
void			wait_time(long long time);
int				ft_atoi(const char *s);

#endif
