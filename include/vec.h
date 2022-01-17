#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include "iterator.h"

typedef struct LinkedList LinkedList;

LinkedList* linkedlist();
void ll_append(LinkedList* list, void* data_to_add);
int ll_is_empty(LinkedList* list);
void ll_destroy(LinkedList* list);
void ll_insert_at(LinkedList* list, int index, void* data_to_insert);
void ll_prepend(LinkedList* list, void* data_to_prepend);
void* ll_get(LinkedList* list, int index);
void* ll_remove(LinkedList* list, int index);
int ll_size(LinkedList* list);
Iterator* ll_iterator(LinkedList* list);

#endif

