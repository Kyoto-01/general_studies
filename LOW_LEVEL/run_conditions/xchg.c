#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 2
#define INCREMENT_COUNT 1000000

int lock;
int shared;

void enter_region(void);
void leave_region(void);
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

void enter_region(void) {
	int temp = 1;

	asm volatile (
		"enter:\n"
		"	lock xchg %0, %1\n"
		"	test %0, %0\n"
		"	jnz enter\n"
		: "+r"(temp), "+m"(lock)
		:
		: "memory"
	);
}

void leave_region(void) {
	lock = 0;
}

void* set_shared(void* args) {
	int i;

	for (i = 0; i < INCREMENT_COUNT; ++i) {
		enter_region();
		++shared;
		leave_region();
	}

	pthread_exit(0);
}
