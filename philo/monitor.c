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
	pthread_mutex_lock(&philo->status);
	if (ft_time() - philo->time > philo->all->time_to_die)
	{
		pthread_mutex_lock(&philo->all->cout);
		pthread_mutex_unlock(&philo->status);
		return (0);
	}
	pthread_mutex_unlock(&philo->status);
	return (1);
}

void	*monitoring(void *data)
{
	t_all	*all;

	all = (t_all *)data;

	int i = 0;
	
	while (1)
	{
		usleep(all->time_to_die - 100);
		i = 0;
		while (i < all->n_philos)
		{
			if (!(philo_alive(&all->philos[i])))
			{
				
				printf("%lu %d died\n", ft_time() - all->start_time, all->philos[i].id);
//				pthread_mutex_lock(&all->cout);
				i = 0;
				while (i < all->n_philos)
				{
					pthread_mutex_destroy(&all->forks[i].mutex);
					i++;
				}
				pthread_mutex_destroy(&all->cout);
				return 0;
			}
			i++;
		}
//		printf ("status %d = %d\n", all->philos->id, all->philos[i].status);
		
	}
	return (0);
}

void	start_monitoring(t_all *all)
{
	pthread_t	p_id;

	pthread_create(&p_id, 0, monitoring, (void *)all);
	pthread_join(p_id, 0);
}
