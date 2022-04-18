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
typedef struct t_philo;

typedef struct s_fork
{
	int		id;
	t_mutex	mutex;
}	t_fork;

typedef struct s_all
{
	unsigned int	n_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
	t_fork			*forks;
	t_philo			*philos;
}	t_all;

typedef struct s_philo
{
	pthread_t	t_id;
	int			id;
	int			ate;
	t_fork		left;
	t_fork		right;
	t_all		p_all;
}	t_philo;

int	ft_atoi(const char *str, int *_res);

#endif
