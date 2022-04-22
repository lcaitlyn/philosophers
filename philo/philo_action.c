/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:54:27 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/04/15 15:54:37 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	ft_fork(t_philo *philo)
{
	if (philo->left->id < philo->right->id)
	{
		pthread_mutex_lock(&philo->left->mutex);
		ft_print(philo->all, philo->time, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right->mutex);
		ft_print(philo->all, philo->time, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->mutex);
		ft_print(philo->all, philo->time, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left->mutex);
		ft_print(philo->all, philo->time, philo->id, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	ft_fork(philo);

	ft_print(philo->all, philo->time, philo->id, "is eating");
	pthread_mutex_lock(&philo->status);
	philo->time = ft_time();
	pthread_mutex_unlock(&philo->status);
	usleep (philo->all->time_to_eat * 1000);
	int j = ft_time();
/*	while ((int)(ft_time - j) < philo->all->time_to_eat)
		usleep(100);*/
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
}

void	*start(void *data)
{
	t_philo		*philo;
	int			i;
	int			j;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->status);
	philo->time = ft_time();
	pthread_mutex_unlock(&philo->status);
	if (philo->id % 2 == 0)
	{
		usleep(2500);
		ft_print(philo->all, philo->time, philo->id, "is thinking");
	}
	i = 0;
	while (i != philo->all->must_eat)
	{
		ft_eat(philo);
		ft_print(philo->all, philo->time, philo->id, "is sleeping");
		j = ft_time();
/*		while ((int)(ft_time - j) < philo->all->time_to_eat)
			usleep(330);*/
		usleep(philo->all->time_to_sleep * 1000);
		ft_print(philo->all, philo->time, philo->id, "is thinking");
		i++;
	}
	return (0);
}

void	ft_start(t_all *all)
{
	pthread_t	p_id;
	pthread_t	t_id;
	t_mutex		m;
	int	i;

	i = 0;
	
	all->start_time = ft_time();
	pthread_mutex_init(&all->cout, 0);
	while (i < all->n_philos)
	{
		all->philos[i].all = all;
		pthread_create(&all->philos[i].t_id, 0, start, (void *)&all->philos[i]);
		pthread_detach(all->philos[i].t_id);
		i++;
	}
	pthread_create(&p_id, 0, monitoring, (void *)all);
	i = 0;
	pthread_join(p_id, 0);
}
