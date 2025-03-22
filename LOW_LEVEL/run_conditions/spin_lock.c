#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 2
#define INCREMENT_COUNT 1000000

int turn;
int shared;

void enter_region(int id);
void leave_region(void);
void* set_shared(void* args);

int main(void) {
	pthread_t threads[THREAD_COUNT];
	int t1Args[1] = {0};
	int t2Args[1] = {1};
	int i;

	pthread_create(&threads[0], NULL, set_shared, (void*)t1Args);
	pthread_create(&threads[1], NULL, set_shared, (void*)t2Args);

	for (i = 0; i < THREAD_COUNT; ++i)
		pthread_join(threads[i], NULL);

	printf("shared = %d\n", shared);
	printf(
		"run condition = %s\n", 
		shared != THREAD_COUNT * INCREMENT_COUNT ? "TRUE" : "FALSE"
	);
}

void enter_region(int id) {
	while (turn != id);
}

void leave_region(void) {
	if (turn == THREAD_COUNT - 1)
		turn = 0;
	else
		++turn;
}

void* set_shared(void* args) {
	int id = ((int*)args)[0];
	int i;

	for (i = 0; i < INCREMENT_COUNT; ++i) {
		enter_region(id);
		++shared;
		leave_region();
	}

	pthread_exit(0);
}
