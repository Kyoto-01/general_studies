#include <unistd.h>
#include <sys/syscall.h>

#include "queue.h"

#ifndef SEMAPHORES_H
#define SEMAPHORES_H

typedef struct semaphore_s {
	int semaphore;
	queue_t* buffer;
} semaphore_t;

semaphore_t* create_semaphore(int value) {
	semaphore_t* tmp = (semaphore_t*)malloc(1 * sizeof(semaphore_t));
	tmp->semaphore = value;
	tmp->buffer = create_queue();

	return tmp;
}

void down(semaphore_t* sem) {
	int tid;

	--(sem->semaphore);

	if (sem->semaphore < 0) {
		tid = syscall(SYS_gettid);
		enqueue(sem, tid);
		signal(SIGUSR1, (void)());
		pause();
	}
}

void up(semaphore_t* sem) {
	int tid, tgid;

	++(sem->semaphore);

	if (sem->semaphore > 0) {
		--(sem->semaphore);
		tgid = getpid();
		tid = dequeue(sem);
		if (tid != NULL)
			syscall(SYS_tgkill, tgid, tid, SIGUSR1); 
	}
}

#endif // semaphores.h
