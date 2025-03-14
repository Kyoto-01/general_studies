#include <windows.h>
#include <stdio.h>

DWORD WINAPI print_char(void *args) {
	int c = ((int*)args)[0];
	int n = ((int*)args)[1];
	int i;

	for (i = 0; i < n; ++i) {
		putchar(c);
		Sleep(1000);
	}

	return 0; // código de terminação do thread
}

int main(void) {
	HANDLE threads[2];
	int t1Args[2] = {'A', 5};
	int t2Args[2] = {'B', 3};

	threads[0] = CreateThread(NULL, 0, print_char, (void*)t1Args, 0, NULL);
	threads[1] = CreateThread(NULL, 0, print_char, (void*)t2Args, 0, NULL);
	
	WaitForMultipleObjects(2, threads, TRUE, INFINITE);

	return 0;
}
