#include "philo.h"
#include <signal.h>

typedef struct s_all
{
	pid_t		p_id;
	pthread_t	t_id;
	int			a;
}	t_all;

void	makefork(void *data)
{
	int	status;
	t_all *all = (t_all *)data;
	
	all->p_id = fork();
	if (all->p_id == 0)
	{
		printf ("Hi from Child %d\n", getpid());
		if (all->a == 0)
			while (1) {
				
			}
		exit (all->a);
	}
	if (all->p_id > 0)
		waitpid(all->p_id, &status, 0);
//	printf ("wait = %d\n", waitpid(pid, &status, 0));
	all->a = 2;
}

int main() //проверка СТатуса в waitpid
{
	t_all	all[3];
	int i = 0;

	printf("main pid = %d\n", getpid());
	while (i < 3)
	{
		all[i].a = i % 2;
		pthread_create(&all[i].t_id, 0, (void *)makefork, (void *)&all[i]);
		i++;
	}
	waitpid(all->p_id, &status, 0);
	usleep(1000);
	if (all[1].a == 2)
	{
		i = 0;
		while (i < 3)
		{
			printf ("kill %d\n", all[i].p_id);
			kill(all[i].p_id, SIGTERM);
			i++;
		}
	}
	/*
	i = 0;
	while (i < 3)
	{
		pthread_join(all[i].t_id, 0);
		i++;
	}*/
	
/*	if (pid > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			printf ("Hi from ChildZXC %d\n", getpid());
			exit (1);
		}
	}*/
/*	printf ("%d\n", waitpid(0, status, 0));
	printf ("status exit 0 = %d\n", *status);*/
	
	
/*	pid = fork();
	if (pid == 0)
	{
		printf ("Hi from ChildZXC %d\n", getpid());
		exit (1);
	}
	if (pid > 0)
		printf ("%d\n", waitpid(pid, status, 0));
	printf ("status exit 1 = %d\n", *status);
	if (WIFEXITED(pid))
		printf ("main %d ended %d\n", getpid(), WEXITSTATUS(pid));*/
	return 0;
}
/*
int main()
{
	pid_t *pid;
	pid = (pid_t *)malloc(5);
	int i = 0;
	int *status;

	while (i < 5)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			printf ("Hi from ChildZXC %d\n", getpid());
			exit (i % 2);
		} */
/*		if (pid[i] > 0)
		{
			waitpid(pid[i], status, 0);
			printf ("status %d = %d", pid[i], *status);
		}*/
/*		i++;
	}
	usleep(1000);
	printf ("getpid = %d\n", getpid());
	
	waitpid(, status, 0);
	printf ("signal  = %d", *status);*/
/*	i = 0;
	while (i < 5)
	{
		waitpid(pid, &signal, 0);
		printf ("signal %d = %d", pid[i], *signal);
		*/
/*		printf ("kill pid = %d\n", pid[i]);
		kill (pid[i], SIGKILL);*/
	//	i++;
//	}
/*	printf ("main %d ended\n", getpid());
	return 0;
}*/


/*
void f(void *data)
{
	exit ((int)data);
}

int main()
{
	int *status;
	pid_t pid;
	pthread_t t_id;
	pid = fork();
	
	if (pid == 0)
	{
		pthread_create(&t_id, 0, (void *)f, (void *)1);
		pthread_join(t_id, 0);
		printf ("mne pohui ya mertv\n");
	}
	if (pid > 0)
		printf ("%d\n", waitpid(pid, status, 0));
	printf ("status exit 0 = %d\n", *status);
	return 0;
}*/
