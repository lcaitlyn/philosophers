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

void	my_usleep(unsigned long long argv)
{
	long long	time;

	time = ft_time();
	while (argv > ft_time() - time)
		usleep(500);
}

void	ft_fork(t_philo *philo)
{
	if (philo->left->id < philo->right->id)
	{
		pthread_mutex_lock(&philo->left->mutex);
		ft_print(philo->all, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right->mutex);
		ft_print(philo->all, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->mutex);
		ft_print(philo->all, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left->mutex);
		ft_print(philo->all, philo->id, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	ft_fork(philo);
	ft_print(philo->all, philo->id, "is eating");
	pthread_mutex_lock(&philo->status);
	philo->time = ft_time();
	philo->ate++;
	my_usleep (philo->all->time_to_eat);
	pthread_mutex_unlock(&philo->status);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
}

void	*start(void *data)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->status);
	philo->time = ft_time();
	pthread_mutex_unlock(&philo->status);
	i = 0;
	while (i != philo->all->must_eat)
	{
		ft_eat(philo);
		ft_print(philo->all, philo->id, "is sleeping");
		pthread_mutex_lock(&philo->status);
		my_usleep(philo->all->time_to_sleep);
		pthread_mutex_unlock(&philo->status);
		ft_print(philo->all, philo->id, "is thinking");
		i++;
	}
	return (0);
}

void	ft_start(t_all *all)
{
	int			i;

	i = 0;
	all->start_time = ft_time();
	pthread_mutex_init(&all->cout, 0);
	while (i < all->n_philos)
	{
		usleep(1);
		all->philos[i].all = all;
		pthread_create(&all->philos[i].t_id, 0, start, (void *)&all->philos[i]);
		pthread_detach(all->philos[i].t_id);
		i++;
	}
	start_monitoring(all);
}
