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

void	*start(void *data)
{
	t_all	*all;

	all = (t_all*)data;
	printf ("Id = %d, Number = %d, t2die = %d", all->id,
			all->n_philos, all->time_to_tie);
}

void	ft_start(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->n_philos)
	{
		pthread_create(&all->philos[i]->t_id, 0, start, (void *)all->philos[i]);
		i++;
	}
	i = 0;
	while (i < all->n_philos)
	{
		pthread_join(&all->philos[i]->t_id, 0);
		i++;
	}
}
