#include "philo.h"


void	*f(void *data)
{
	int *tmp = (int *)data;
	int i = -1;
	while (++i < 10)
		*tmp += 1;
	return 0;
}

int main()
{
	t_mutex
	int	tmp = 0;
	pthread_t	id;
	pthread_t	id2;
	pthread_create(&id, 0, f, &tmp);
	pthread_create(&id2, 0, f, &tmp);
	while (tmp < 10)
		tmp++;
	
	pthread_join(id, 0);
	pthread_join(id2, 0);
//	printf ("I'm in main");
	printf ("%d\n", tmp);
	return 0;
}
