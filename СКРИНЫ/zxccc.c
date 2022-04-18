#include "philo.h"

void	f(char **line)
{
	*line = "Hello";
}

int main()
{
	pid_t pid;
	char *line = malloc(10);
	
	line = "zxc";
	pid = fork();
	if (pid == 0)
		f(&line);
	printf ("%s", line);
	return 0;
}
