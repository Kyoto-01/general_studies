#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 2
#define INCREMENT_COUNT 1000000

int shared;

void* set_shared(void* args);

int main(void) {
	pthread_t threads[THREAD_COUNT];
	int i;

	for (i = 0; i < THREAD_COUNT; ++i)
		pthread_create(&threads[i], NULL, set_shared, NULL);

	for (i = 0; i < THREAD_COUNT; ++i)
		pthread_join(threads[i], NULL);

	printf("shared = %d\n", shared);
	printf(
		"run condition = %s\n", 
		shared != THREAD_COUNT * INCREMENT_COUNT ? "TRUE" : "FALSE"
	);
}

void* set_shared(void* args) {
	int i;

	for (i = 0; i < INCREMENT_COUNT; ++i)
		++shared;
		// Ex.: 
		// * shared = 0
		// * Um thread obtém o valor de shared e é bloqueado
		// 	antes de incrementá-lo
		// * Outro thread e executado
		// * shared = 1
		// * Thread anterior é desbloqueado, para ele shared ainda
		//	é 0
		// * shared = 1
		// *** shared deveria ser 2 nesse momento, mas a condição
		// 	de corrida impediu que isso acontecesse.

	pthread_exit(0);
}
