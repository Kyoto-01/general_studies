#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "tree.h"

#define READER_NUM 3

int myVals[5][3] = {
	{0, 0, 0}, 
	{1, 1, 1},
	{2, 2, 2},
	{3, 3, 3},
	{4, 4, 4}
};
node_t* myNodes[5];
tree_t* myTree;

tree_t* start_test_tree() {
	/* ------------------
	
		 A
		/ \
	       B   E
	      / \
	     C   D
	
	------------------- */

	int i;

	for (i = 0; i < 6; ++i)
		myNodes[i] = node_init((void*)(myVals + i));
		
	tree_insert(myNodes[0], myNodes[1]);
	tree_insert(myNodes[0], myNodes[4]);
	tree_insert(myNodes[1], myNodes[2]);
	tree_insert(myNodes[1], myNodes[3]);

	return tree_init(myNodes[0]);
}

void test_tree_nodes(node_t* node) {
	int i;
	
	printf(
		"%d, %d, %d\t%s\n", 
		((int*)node->data)[0],
		((int*)node->data)[1],
		((int*)node->data)[2],
		(
		 	(((int*)node->data)[0] == ((int*)node->data)[1]) &&
			(((int*)node->data)[1] == ((int*)node->data)[2]) 
			? "TRUE" : "FALSE"
		)
	);

	for (i = 0; i < node->childCount; ++i)
		test_tree_nodes(node->childs[i]);
}

void write_tree_node(node_t* node) {
	int randValue, randSleep, i;

	randValue = (int)(random() % 100);
	randSleep = (int)(random() % 5);

	for (i = 0; i < 3; ++i) {
		((int*)node->data)[i] = randValue;
		sleep(randSleep);
	}

	for (i = 0; i < node->childCount; ++i)
		write_tree_node(node->childs[i]);
}	

void* writer_task(void* args) {
	while (1) {
		write_tree_node(myTree->root);
	}
}

void* reader_task(void* args) {
	int maxSleep = ((int*)args)[0];
	int randomSleep;

	while (1) {
		test_tree_nodes(myTree->root);
		randomSleep = (int)(random() % maxSleep);
		sleep(randomSleep);
	}

	return 0;	
}

int main(int argc, char* argv[]) {
	pthread_t writer;
	pthread_t readers[READER_NUM];
	int readerMaxSleep = 5, i;
	
	myTree = start_test_tree(myVals, myNodes);

	writer = pthread_create(&writer, NULL, writer_task, NULL);
	for (i = 0; i < READER_NUM; ++i)
		pthread_create(&readers[i], NULL, reader_task, &readerMaxSleep);

	pthread_join(writer, NULL);
	for (i = 0; i < READER_NUM; ++i)
		pthread_join(readers[i], NULL);

	return 0;
}
