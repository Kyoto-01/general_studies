#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>

#include "queue.h"
#include "xchg.h"

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

	enter_region();

	if (sem->semaphore > 0) {
		--(sem->semaphore);
		leave_region();
	} else {
		tid = syscall(SYS_gettid);
		enqueue(sem->buffer, tid);
		while (sem->semaphore <= 0) {
			leave_region();
			pause();
		}
	}
}

void up(semaphore_t* sem) {
	int tid, tgid;

	enter_region();

	++(sem->semaphore);

	if (sem->semaphore > 0) {
		tgid = getpid();
		tid = dequeue(sem->buffer);
		if (tid != 0) {
			--(sem->semaphore);
			syscall(SYS_tgkill, tgid, tid, SIGUSR1); 
		}
	}

	leave_region();
}

#endif // semaphores.h
