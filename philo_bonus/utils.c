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

int	ft_exit(int i)
{
	if (i)
		printf ("Error: Malloc error with philos\n");
	else
	{
		printf ("Error! Wrong arguments\n./philo ");
		printf ("[number_of_philosophers] [time_to_die] [time_to_eat] ");
		printf ("[time_to_sleep] {number_of_times_each_philosopher_must_eat}\n");
	}
	exit (1);
}

int	ft_clear(t_all *all)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (++i < all->n_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < all->n_philos)
			{
				kill(all->philos[i].p_id, SIGKILL);
				i++;
			}
			break ;
		}
	}
	sem_close(all->forks);
	sem_close(all->cout);
	sem_unlink("forks");
	sem_unlink("cout");
	free(all->philos);
	return (0);
}

unsigned long	ft_time(void)
{
	t_timeval		tv;
	unsigned long	time;

	gettimeofday(&tv, 0);
	return (time = tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
