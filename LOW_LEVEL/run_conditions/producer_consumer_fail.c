#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

int items[N];
int count = 0;
sem_t empty, full;

int produce_item(void) {
	return rand();
}

void insert_item(int item) {
	items[count] = item;
}

int remove_item(void) {
	int item = items[count];
	items[count] = 0;

	return item;
}

void consume_item(int item) {
	printf("%d", item);
}

void* producer(void* args) {
	int item;
	
	while (1) {
		item = produce_item();

		sem_wait(&empty);

		insert_item(item);
		++count;

		sem_post(&full);
	}

	return 0;
}

void* consumer(void* args) {
	int item;

	while(1) {
		sem_wait(&full);

		item = remove_item();
		--count;

		sem_post(&empty);

		consume_item(item);
	}

	return 0;
}

int main(void) {
	pthread_t thdProducer, thdConsumer;
	
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);	

	pthread_create(&thdConsumer, NULL, consumer, NULL);
	pthread_create(&thdProducer, NULL, producer, NULL);

	pthread_join(thdConsumer, NULL);

	return 0;
}
