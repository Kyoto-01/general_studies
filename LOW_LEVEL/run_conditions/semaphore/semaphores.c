#include <stdio.h>
#include <pthread.h>

#include "semaphores.h"

#define THREAD_COUNT 10
#define INCREMENT_COUNT 1000000

semaphore_t* lock;
int shared;

void* set_shared(void* args);

int main(void) {
        pthread_t threads[THREAD_COUNT];
        int i;

        lock = create_semaphore(1);

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

void sighand(int sig) {}

void* set_shared(void* args) {
        int i;

	signal(SIGUSR1, sighand);

        for (i = 0; i < INCREMENT_COUNT; ++i) {
                down(lock);
                ++shared;
                up(lock);
        }

        return 0;
}
