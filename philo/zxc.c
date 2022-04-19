#include "philo.h"

t_fork	*init_forks(int size)
{
	t_fork	*forks;
	int		i;

	forks = (t_fork *)malloc(sizeof(t_fork) * size);
	if (!forks)
		return (0);
	i = 0;
	while (i < size)
	{
		forks[i].id = i + 1;
		if (pthread_mutex_init(&forks[i].mutex, 0))
		{
			free (forks);
			return (0);
		}
		i++;
	}
	return (forks);
}

int main()
{
	int i = 0;
	t_fork *forks = init_forks(5);
	while (i < 5)
	{
		printf ("%d\n", forks[i].id);
		i++;
	}
	if (!pthread_mutex_lock(&forks[0].mutex))
		printf ("Z\n");
//	pthread_mutex_unlock(&forks[0].mutex);
	if (!pthread_mutex_lock(&forks[0].mutex))
		printf ("x\n");\
	return 0;
}
