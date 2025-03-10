#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Rotina que será executada por cada thread
// ela imprime o caractere "c" "n" vezes
void *print_char(void *args) {
	int c, n, i;
	
	// Obtendo argumentos passados para a função pthread_create
	c = ((int*)args)[0];
	n = ((int*)args)[1];

	for (i = 0; i < n; ++i) {
		putchar(c);
		sleep(.5);
	}
}

int main(void) {
	// Serão criados 2 threads
	pthread_t threads[2];
	// O primeiro imprime o caractere "A" "5" vezes
	int t1Args[2] = {'A', 5};
	// O segundo imprime o caractere "B" "3" vezes
	int t2Args[2] = {'B', 3};
	int i;

	// Criando threads
	pthread_create(&threads[1], NULL, print_char, (void*)t1Args);
	pthread_create(&threads[2], NULL, print_char, (void*)t2Args);
	
	// Utilizando a função pthread_join para fazer o
	// thread principal aguardar pela conclusão dos demais
	for (i = 0; i < 2; ++i)
		pthread_join(threads[i], NULL);

	return 0;
}

/*
	SAÍDA --->  ABBABAAA
*/
