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

void	ft_print(t_all *all, int id, char *str)
{
	sem_wait(all->cout);
	printf("%lu %d %s\n", ft_time() - all->start_time, id, str);
	sem_post(all->cout);
}

void	*monitoring(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		usleep(500);
		if ((int)(ft_time() - philo->time) > philo->all->time_to_die)
		{
			sem_wait(philo->all->cout);
			printf("%lu %d died\n", ft_time() - philo->all->start_time,
				philo->id);
			exit (1);
		}
		if (philo->all->must_eat != -1 && philo->ate >= philo->all->must_eat)
			exit(0);
	}
	return (0);
}
