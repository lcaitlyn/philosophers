/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:33:45 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/04/20 15:33:46 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_all *all, unsigned long time, int id, char *str)
{
	pthread_mutex_lock(&all->cout);
	printf("%lu %d %s\n", ft_time() - all->start_time, id, str);
	pthread_mutex_unlock(&all->cout);
}

int	philo_alive(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->status);
	if (ft_time() - philo->time >= philo->all->time_to_die
		&& philo->ate != philo->all->must_eat)
	{
		pthread_mutex_lock(&philo->all->cout);
		printf("%lu %d died\n", ft_time() - philo->all->start_time, philo->id);
		i = 0;
		while (i < philo->all->n_philos)
		{
			pthread_mutex_destroy(&philo->all->forks[i].mutex);
			i++;
		}
		pthread_mutex_destroy(&philo->all->cout);
		pthread_mutex_unlock(&philo->status);
		return (0);
	}
	pthread_mutex_unlock(&philo->status);
	return (1);
}

void	*monitoring(void *data)
{
	t_all	*all;
	int		i;
	int		j;

	all = (t_all *)data;
	j = all->n_philos;
	while (j)
	{
		usleep(500);
		i = 0;
		while (i < all->n_philos)
		{
			if (!(philo_alive(&all->philos[i])))
				return (0);
			pthread_mutex_lock(&all->philos[i].status);
			if (all->philos[i].ate == all->must_eat && all->philos[i].done)
			{
				j--;
				all->philos[i].done = 0;
			}
			pthread_mutex_unlock(&all->philos[i].status);
			i++;
		}		
	}
	return (0);
}

void	start_monitoring(t_all *all)
{
	pthread_t	p_id;
	int			i;

	pthread_create(&p_id, 0, monitoring, (void *)all);
	pthread_join(p_id, 0);
	i = 0;
	while (i < all->n_philos)
	{
		pthread_mutex_destroy(&all->philos[i].status);
		i++;
	}
}
