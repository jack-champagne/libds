#ifndef LIBDS_BST
#define LIBDS_BST

// This file contains the specification for a binary search tree implemented in C
// with generic types (void*)

typedef struct BSTree BSTree;

BSTree* bstree();
void insert(void* new_data);
char has(void* data_to_find);
void* remove(void* data_to_remove);

#endif