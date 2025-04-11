#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 10

sem_t h, g, t;

void* hitchcock(void* args) {
	printf(" hhhhh ");

	sem_wait(&h);
	printf("Hitchcock ---> ");
	sem_post(&g);

	printf(" HHHHH ");
	
	return 0;
}

void* goddard(void* args) {
	printf(" ggggg ");

	sem_wait(&g);
	printf("Goddard ---> ");
	sem_post(&t);

	printf(" GGGGG ");

	return 0;
}

void* tarantino(void* args) {
	printf(" ttttt ");

	sem_wait(&t);
	printf("Tarantino ---> ");
	sem_post(&h);

	printf(" TTTTT ");

	return 0;
}

int main(void) {
	pthread_t threads[THREAD_COUNT];
	int i;

	sem_init(&h, 0, 1);
	sem_init(&g, 0, 0);
	sem_init(&t, 0, 0);

	for (i = 0; i < THREAD_COUNT; ++i) {
		pthread_create(&threads[i], NULL, hitchcock, NULL);
		pthread_create(&threads[i], NULL, goddard, NULL);
		pthread_create(&threads[i], NULL, tarantino, NULL);
	}

	for (i = 0; i < THREAD_COUNT; ++i)
		pthread_join(threads[i], NULL);
		
	return 0;
}
