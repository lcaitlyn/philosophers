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

int	philo_alive(t_philo *philo)
{
	printf ("i = %d T = %lu, T_2_D = %d\n", philo->id, ft_time() - philo->time, philo->all.time_to_die);
	if (ft_time() - philo->time >= philo->all.time_to_die)
	{
		return (0);
		philo->status = 1;
		pthread_mutex_lock(&philo->all.cout);
	}
	else
		return (1);
}

void	ft_fork(t_philo *philo)
{
	if (philo->left->id < philo->right->id)
	{
		pthread_mutex_lock(&philo->left->mutex);
		ft_print(&philo->all, philo->time, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right->mutex);
		ft_print(&philo->all, philo->time, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->mutex);
		ft_print(&philo->all, philo->time, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left->mutex);
		ft_print(&philo->all, philo->time, philo->id, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	ft_fork(philo);

	ft_print(&philo->all, philo->time, philo->id, "is eating");
	philo->time = ft_time();
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
	{
		usleep(2500);
		ft_print(&philo->all, philo->time, philo->id, "is thinking");
	}
	int i = 0;
	while (i != philo->all.must_eat)
	{
		if (!philo_alive(philo))
		{
			ft_print(&philo->all, philo->time, philo->id, "died");
			pthread_mutex_lock (&philo->all.cout);
			return (0);
		}
		ft_eat(philo);
		if (!philo_alive(philo))
		{
			ft_print(&philo->all, philo->time, philo->id, "died");
			pthread_mutex_lock (&philo->all.cout);
			return (0);
		}
		ft_print(&philo->all, philo->time, philo->id, "is sleeping");
		usleep(philo->all.time_to_sleep * 1000);
		if (!philo_alive(philo))
		{
			ft_print(&philo->all, philo->time, philo->id, "died");
			pthread_mutex_lock (&philo->all.cout);
			return (0);
		}
		ft_print(&philo->all, philo->time, philo->id, "is thinking");
		i++;
	}
	return (0);
}

void	ft_start(t_all *all)
{
	int	i;

	i = 0;
	all->start_time = ft_time();
	pthread_mutex_init(&all->cout, 0);
	while (i < all->n_philos)
	{
		all->philos[i].all = *all;
		pthread_create(&all->philos[i].t_id, 0, start, (void *)&all->philos[i]);
		i++;
	}
	start_monitoring(all);
	i = 0;
	while (i < all->n_philos)
	{
		pthread_join(all->philos[i].t_id, 0);
		i++;
	}
	
}
