#include <stdlib.h>
#include <stdio.h>

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

void tree_dbg(node_t* root) {
	if (root != NULL) {
		printf("%d\n", *((int*)(root->data)));
		for (int i = 0; i < root->childCount; ++i) {
			tree_dbg((root->childs)[i]);
		}
	}
}

int main() {
	int vals[2] = {1, 2};
	node_t* myRoot = node_init((void*)&vals[0]);
	tree_t* myTree = tree_init(myRoot);
	node_t* myNode = node_init((void*)&vals[1]);
	tree_insert(myTree->root, myNode);
	tree_dbg(myTree->root);

	return 0;
}
