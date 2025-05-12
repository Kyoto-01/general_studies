// tree.h

#include <stdlib.h>

#ifndef __TREE_H__
#define __TREE_H__

typedef struct node_s {
	void* data;
	int childCount;
	struct node_s** childs;
} node_t;

typedef struct tree_s {
	node_t* root;
} tree_t;

node_t* node_init(void* data) {
	node_t* tmpNode = (node_t*)malloc(sizeof(node_t));
	tmpNode->data = data;
	tmpNode->childCount = 0;
	tmpNode->childs = NULL;

	return tmpNode;
}

void node_update(node_t* node, node_t* parent, int index, void* data) {
	node_t* newNode = (node_t*)malloc(sizeof(node_t));

	newNode->data = data;
	newNode->childs = node->childs;

	if (parent != NULL)
		parent->childs[index] = newNode;
}

tree_t* tree_init(node_t* root) {
	tree_t* tmpTree = (tree_t*)malloc(sizeof(tree_t));
	tmpTree->root = root;

	return tmpTree;
}

void tree_insert(node_t* parent, node_t* node) {
	parent->childs = realloc(parent->childs, sizeof(node_t*));
	parent->childCount += 1;
	parent->childs[parent->childCount - 1] = node; 
}

#endif // tree.h
