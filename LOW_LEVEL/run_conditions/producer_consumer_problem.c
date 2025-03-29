#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

int items[N];
pthread_mutex_t mutex;
pthread_cond_t cond;
int count = 0;

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
		pthread_mutex_lock(&mutex);
		if (count == N) pthread_cond_wait(&cond, &mutex);
		insert_item(item);
		++count;
		if (count == 1) pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
}

void* consumer(void* args) {
	int item;

	while(1) {
		pthread_mutex_lock(&mutex);
		if (count == 0) pthread_cond_wait(&cond, &mutex);
		item = remove_item();
		--count;
		if (count == N - 1) pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		consume_item(item);
	}
}

int main(void) {
	pthread_t thdProducer, thdConsumer;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_create(&thdConsumer, NULL, consumer, NULL);
	pthread_create(&thdProducer, NULL, producer, NULL);

	pthread_join(thdConsumer, NULL);

	return 0;
}
