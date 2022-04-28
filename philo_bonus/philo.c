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

int	init_philos(t_all *all)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * all->n_philos);
	if (!philos)
		return (ft_exit(1));
	i = 0;
	while (i < all->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].ate = 0;
		i++;
	}
	all->philos = philos;
	return (0);
}

int	init_arg(t_all *all, int argc, char *argv[])
{
	if (ft_atoi(argv[0], &all->n_philos))
		return (ft_exit(0));
	if (ft_atoi(argv[1], &all->time_to_die))
		return (ft_exit(0));
	if (ft_atoi(argv[2], &all->time_to_eat))
		return (ft_exit(0));
	if (ft_atoi(argv[3], &all->time_to_sleep))
		return (ft_exit(0));
	if (argc == 4)
		all->must_eat = -1;
	else if (argc == 5 && ft_atoi(argv[4], &all->must_eat))
		return (ft_exit(0));
	if (all->n_philos < 1 || all->time_to_eat < 10
		|| all->time_to_sleep < 10 || all->time_to_die < 10
		|| (all->must_eat < 1 && argc == 5))
		return (1);
	sem_unlink("forks");
	all->forks = sem_open("forks", O_CREAT, S_IRWXU, all->n_philos);
	sem_unlink("cout");
	all->cout = sem_open("cout", O_CREAT, S_IRWXU, 1);
	if (all->forks == SEM_FAILED || all->cout == SEM_FAILED)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all	all;

	if (argc != 5 && argc != 6)
		return (ft_exit(0));
	if (init_arg(&all, --argc, ++argv))
		return (ft_exit(0));
	if (init_philos(&all))
		return (1);
	ft_start(&all);
	return (0);
}
