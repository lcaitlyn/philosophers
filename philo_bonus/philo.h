/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:33:20 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/04/11 16:33:33 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_timeval;
typedef struct s_philo	t_philo;

typedef struct s_all
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	unsigned long	start_time;
	sem_t			*cout;
	sem_t			*forks;
	t_philo			*philos;
}	t_all;

typedef struct s_philo
{
	pid_t			p_id;
	pthread_t		t_id;
	int				id;
	int				ate;
	unsigned long	time;
	t_all			*all;
}	t_philo;

int				ft_atoi(const char *str, int *_res);
void			ft_start(t_all *all);
int				ft_exit(int i);
int				ft_clear(t_all *all);
unsigned long	ft_time(void);
void			ft_print(t_all *all, int id, char *str);
int				philo_alive(t_philo *philo);
void			*monitoring(void *data);

#endif
