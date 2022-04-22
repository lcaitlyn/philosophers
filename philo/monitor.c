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

void	*monitoring(void *data)
{
	t_all	*all;

	all = (t_all *)data;

	int i = 0;
	while (1)
	{
		
		if (all->philos[i].status)
		{
			pthread_mutex_lock (&all->cout);
			all->philos[i].ate = all->must_eat;
			return (0);
		}
		if (i >= all->n_philos - 1)
			i = -1;
		i++;
	}
	return (0);
}

void	start_monitoring(t_all *all)
{
	pthread_t	p_id;

	pthread_create(&p_id, 0, monitoring, (void *)all);
	pthread_join(p_id, 0);
}
