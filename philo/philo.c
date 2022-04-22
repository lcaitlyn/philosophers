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
	t_fork	*forks;
	int		i;

	forks = (t_fork *)malloc(sizeof(t_fork) * all->n_philos);
	if (!forks)
		return (1);
	i = 0;
	while (i < all->n_philos)
	{
		forks[i].id = i + 1;
		if (pthread_mutex_init(&forks[i].mutex, 0))
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
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * all->n_philos);
	if (!philos)
		return (ft_exit(all));
	i = 0;
	while (i < all->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].ate = 0;
		philos[i].left = &all->forks[i];
		philos[i].right = &all->forks[(i + 1) % all->n_philos];
		philos[i].status = 0;
		i++;
	}
	all->philos = philos;
	return (0);
}

int	init_arg(t_all *all, int argc, char *argv[])
{
	
	if (ft_atoi(argv[0], &all->n_philos))
		return (1);
	if (ft_atoi(argv[1], &all->time_to_die))
		return (1);
	if (ft_atoi(argv[2], &all->time_to_eat))
		return (1);
	if (ft_atoi(argv[3], &all->time_to_sleep))
		return (1);
	if (argc == 4)
		all->must_eat = -1;
	else if (argc == 5 && ft_atoi(argv[4], &all->must_eat))
		return (1);
	if (all->n_philos < 1 || all->time_to_eat < 10
		|| all->time_to_sleep < 10 || all->time_to_die < 10
		|| (all->must_eat < 1 && argc == 5))
		return (1);
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
	ft_start(&all);
	return (ft_clear(&all));
}
