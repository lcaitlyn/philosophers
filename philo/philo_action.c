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

void	ft_putnbr(int n)
{
	unsigned int	nb;
	char			c;

	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		write (1, "-", 1);
		n = n * -1;
	}
	else if (n > 2147483647)
	{
		write (1, "2", 1);
		n = 147483647;
	}
	nb = (unsigned int)n;
	if (n > 9)
		ft_putnbr(nb / 10);
	c = (char )(nb % 10 + 48);
	write (1, &c, 1);
}

void	*start(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	philo->time = ft_time();
	printf ("%lu id = %d\n",
			philo->time - philo->all.start_time, philo->id);
	sleep(1);
	ft_putnbr(ft_time() - philo->all.start_time);
	printf ("%lu id = %d\n",
			ft_time() - philo->all.start_time, philo->id);
	ft_putnbr(ft_time() - philo->all.start_time);
	return (0);
}

void	ft_start(t_all *all)
{
	int	i;

	i = 0;
	all->start_time = ft_time();
	while (i < all->n_philos)
	{
		all->philos[i].all = *all;
		pthread_create(&all->philos[i].t_id, 0, start, (void *)&all->philos[i]);
		i++;
	}
	i = 0;
	while (i < all->n_philos)
	{
		pthread_join(all->philos[i].t_id, 0);
		i++;
	}
}
