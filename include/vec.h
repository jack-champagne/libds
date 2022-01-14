#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <stdlib.h>
#include "iterator.h"
#include "node.h"

typedef struct LinkedList {
    Node* head;
    int size;
    Node* tail; 
} LinkedList;

#define LL_MALLOC_SIZE 10000;

LinkedList* linked_list();
void ll_append(LinkedList* list, void* data_to_add);
int ll_is_empty(LinkedList* list);
void ll_destroy(LinkedList* list);
void ll_insert_at(LinkedList* list, int index, void* data_to_insert);
void ll_prepend(LinkedList* list, void* data_to_prepend);
void* ll_get(LinkedList* list, int index);
void* ll_remove(LinkedList* list, int index);
Node* get_node(LinkedList* list, int index);
Iterator* iterator(LinkedList* list);

#endif

