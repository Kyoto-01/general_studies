#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node_s {
	int value;
	struct queue_node_s* next;
} queue_node_t;

typedef struct queue_s {
	queue_node_t* head;
	queue_node_t* tail;
} queue_t;

queue_t* create_queue(void) {
	queue_t* queue = (queue_t*)malloc(1 * sizeof(queue_t));
	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

int is_void(queue_t* queue) {
	return queue->head == NULL;
}

void enqueue(queue_t* queue, int value) {
	queue_node_t* node = (queue_node_t*)malloc(1 * sizeof(queue_node_t));
	node->value = value;
	node->next = NULL;

	if (is_void(queue))
		queue->head = node;
	else
		queue->tail->next = node;

	queue->tail = node;
}

int dequeue(queue_t* queue) {
	queue_node_t* node;
	int value = 0;

	if (!is_void(queue)) {
		node = queue->head;
		value = queue->head->value;
		queue->head = queue->head->next;
		free(node);
	}

	return value;
}

#endif // queue.h
