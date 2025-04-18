#ifndef XCHG_H
#define XCHG_H

int xchgLock;

void enter_region(void);
void leave_region(void);

void enter_region(void) {
	int temp = 1;

	asm volatile (
		"enter:\n"
		"	lock xchg %0, %1\n"
		"	test %0, %0\n"
		"	jnz enter\n"
		: "+r"(temp), "+m"(xchgLock)
		:
		: "memory"
	);
}

void leave_region(void) {
	xchgLock = 0;
}

#endif // xchg.h
