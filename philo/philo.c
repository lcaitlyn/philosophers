/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:39:46 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/04/15 13:39:47 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_all *all)
{
	t_fork	forks;
	int		i;

	forks = (t_fork)malloc(sizeof(t_fork) * all->n_philos);
	if (forks)
		return (1);
	i = 0;
	while (i < all->n_philos)
	{
		forks[i]->id = i;
		if (pthread_mutex_init(&forks[i]->mutex, 0))
		{
			free (forks);
			return (1);
		}
		i++;
	}
	all->forks = forks;
	return (0);
}

int	init_philos(t_all *all)
{
	t_philo	philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * all->n_philos);
	if (!philos)
		return (ft_exit(all));
	i = 0;
	while (i < all->n_philo)
	{
		philos[i]->id = i;
		philos[i]->ate = 0;
		philos[i]->left = all->forks[i];
		philos[i]->right = all->forks[(i + 1) % all->n_philo];
		i++;
	}
	all->philos = philos;
	return (0);
}

int	init_arg(t_all *all, int argc, char *argv[])
{
	
	if (ft_atoi(argv[0], all->philos))
		return (1);
	if (ft_atoi(argv[1], all->time_to_die))
		return (1);
	if (ft_atoi(argv[2], all->time_to_eat))
		return (1);
	if (ft_atoi(argv[3], all->time_to_sleep))
		return (1);
	if (argc == 5 && ft_atoi(argv[0], all->must_eat))
		return (1);
	else
		all->must_eat = -1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all	all;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_arg(&all, --argc, ++argv))
		return (1);
	if (init_forks(&all))
		return (1);
	if (init_philos(&all))
		return (1);
	ft_start(all);
	return (0);
}
