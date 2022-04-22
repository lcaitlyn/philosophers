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
	printf ("print cout = %x\n", (unsigned)&all->cout);
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
		i = 0;
		while (i < all->n_philos)
		{
			if (!(philo_alive(&all->philos[i])))
			{
				printf ("cout = %x\n", (unsigned)&all->cout);
				
				ft_print(all, all->philos[i].time, all->philos[i].id, "died");
				pthread_mutex_lock(&all->cout);
				i = 0;
				while (i < all->n_philos)
				{
					all->philos[i].status = 0;
					printf ("%d d\n", i);
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
