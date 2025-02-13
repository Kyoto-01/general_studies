#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 10

void* action(void* tid) {
	printf("Thread %d: START\n", tid);
	sleep(1);
	printf("Thread %d: END\n", tid);
	pthread_exit(NULL);
}

int main(void) {
	pthread_t actions[NUMBER_OF_THREADS];
	int status, i;

	for (i = 0; i < NUMBER_OF_THREADS; ++i) {
		status = pthread_create(
			&actions[i],
			NULL,
			action,
			(void*)i
		);

		if (status != 0) {
			printf("Falha ao criar o Thread.\n");
			return EXIT_FAILURE;
		}
	}

	for (i = 0; i < NUMBER_OF_THREADS; ++i) {
		pthread_join(actions[i], NULL);
	}

	return EXIT_SUCCESS;
}
