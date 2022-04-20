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
		pthread_mutex_lock(&philo->right->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right->mutex);
		pthread_mutex_lock(&philo->left->mutex);
	}
	printf("%lu %d has taken a fork\n", ft_time() - philo->time,
		   philo->id);
	printf("%lu %d has taken a fork\n", ft_time() - philo->time,
		   philo->id);
}

void	ft_eat(t_philo *philo)
{
	ft_fork(philo);
	printf ("%lu %d is eating\n", ft_time() - philo->time, philo->id);
	usleep (philo->all.time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
}

void	*start(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	philo->time = ft_time();
	if (philo->id % 2 == 0)
		usleep(2500);
	while (1)
	{
		ft_eat(philo);
		printf ("%lu %d is sleeping\n", ft_time() - philo->time, philo->id);
		usleep(philo->all.time_to_sleep * 1000);
		
	}
	return (0);
}

void	ft_start(t_all *all)
{
	int	i;

	i = 0;
	all->start_time = ft_time();
	while (i < all->n_philos)
	{
		all->philos[i].all = *all;
		pthread_create(&all->philos[i].t_id, 0, start, (void *)&all->philos[i]);
		i++;
	}
	i = 0;
	while (i < all->n_philos)
	{
		pthread_join(all->philos[i].t_id, 0);
		i++;
	}
}
