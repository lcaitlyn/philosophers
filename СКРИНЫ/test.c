#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*printhello(void *data)
{
	int	my_data = (int)data;
	pthread_detach(pthread_self());
	printf("Hello from new thread - got %d\n", my_data);
	pthread_exit(NULL);
}

int	main()
{
	int			rc;
	pthread_t	thread_id;
	int			t = 11;

	rc = pthread_create(&thread_id, NULL, printhello, (void *)&t);
	if (rc)
	{
		printf("\n ERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	}
	printf("\n Created new thread (%u) ... \n", (int)thread_id);
	pthread_exit(NULL);
}
