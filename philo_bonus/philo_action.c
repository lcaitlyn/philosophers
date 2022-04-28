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

void	start(t_philo *philo)
{
	philo->time = ft_time();
	pthread_create(&philo->t_id, 0, monitoring, (void *)philo);
	pthread_detach(philo->t_id);
	while (1)
	{
		ft_print(philo->all, philo->id, "is thinking");
		sem_wait(philo->all->forks);
		ft_print(philo->all, philo->id, "has taken fork");
		sem_wait(philo->all->forks);
		ft_print(philo->all, philo->id, "has taken fork");
		ft_print(philo->all, philo->id, "is eating");
		philo->time = ft_time();
		my_usleep (philo->all->time_to_eat);
		sem_post(philo->all->forks);
		sem_post(philo->all->forks);
		philo->ate++;
		ft_print(philo->all, philo->id, "is sleeping");
		my_usleep(philo->all->time_to_sleep);
	}
}

void	ft_start(t_all *all)
{
	int			i;

	i = 0;
	all->start_time = ft_time();
	while (i < all->n_philos)
	{
		all->philos[i].all = all;
		all->philos[i].p_id = fork();
		if (all->philos[i].p_id == -1)
			ft_clear(all);
		else if (all->philos[i].p_id == 0)
			start(&all->philos[i]);
		i++;
	}
	ft_clear(all);
}
