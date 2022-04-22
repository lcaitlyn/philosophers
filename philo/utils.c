/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:02:11 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/04/15 14:02:22 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, int *_res)
{
	long long	res;
	int			sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	if (*str != 0)
		return (1);
	*_res = (res * sign);
	return (0);
}

int	ft_exit(t_all *all)
{
	free(all->forks);
	return (1);
}

int	ft_clear(t_all *all)
{
	
	int i = 0;
	while (i < all->n_philos)
	{
		pthread_mutex_destroy(&all->forks[i].mutex);
		i++;
	}
	free (all->forks);
	free (all->philos);
	return (0);
}

unsigned long	ft_time(void)
{
	t_timeval		tv;
	unsigned long	time;
	
	gettimeofday(&tv, 0);
	return (time = tv.tv_sec * 1000 + tv.tv_usec / 1000);
/*	time = tv.tv_sec * 1000 + (tv.tv_usec - tv.tv_usec % 100000) / 1000;
	return (time);*/
}
