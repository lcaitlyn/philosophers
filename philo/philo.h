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

typedef struct timeval t_timeval;
typedef pthread_mutex_t t_mutex;
typedef struct s_philo t_philo;

typedef struct s_fork
{
	int		id;
	t_mutex	mutex;
}	t_fork;

typedef struct s_all
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	unsigned long	start_time;
	t_mutex			cout;
	t_fork			*forks;
	t_philo			*philos;
}	t_all;

typedef struct s_philo
{
	pthread_t		t_id;
	int				id;
	int				ate;
	unsigned long	time;
	int				status;
	t_fork			*left;
	t_fork			*right;
	t_all			*all;
}	t_philo;

int				ft_atoi(const char *str, int *_res);
void			ft_start(t_all *all);
int				ft_exit(t_all *all);
int				ft_clear(t_all *all);
unsigned long	ft_time(void);
void			start_monitoring(t_all *all);
void			ft_print(t_all *all, unsigned long time, int id, char *str);
int				philo_alive(t_philo *philo);
void			*monitoring(void *data);

#endif
