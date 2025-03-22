#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 2
#define INCREMENT_COUNT 1000000

// Características
// ---------------
// * Permite apenas 2 processos ou threads
// * Usa busy waiting
// * Diferente do Spin Lock, o acesso às regiões
// 	críticas não ocorre de forma explicitamente
// 	ordenada.

int turn;
int interested[THREAD_COUNT];
int shared;

void enter_region(int id);
void leave_region(int id);
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
	int other;

	other = 1 - id;
	interested[id] = 1;
	turn = id;
	
	while (turn == id && interested[other] == 1);
}

void leave_region(int id) {
	interested[id] = 0;
}

void* set_shared(void* args) {
	int id = ((int*)args)[0];
	int i;

	for (i = 0; i < INCREMENT_COUNT; ++i) {
		enter_region(id);
		++shared;
		leave_region(id);
		// quando eu cheguei aqui, fui bloqueado
		// veio outro thread e incrementou shared "primeiro"
	}

	pthread_exit(0);
}
