#ifndef CDLVEC_H
#define CDLVEC_H

#include "iterator.h"
#include <stdio.h>

typedef struct CDLinkedList CDLinkedList;

CDLinkedList* cdlinkedlist();
void cdll_append(CDLinkedList* list, void* data_to_add);
int cdll_is_empty(CDLinkedList* list);
void cdll_destroy(CDLinkedList* list);
void cdll_insert_at(CDLinkedList* list, int index, void* data_to_insert);
void cdll_prepend(CDLinkedList* list, void* data_to_prepend);
void* cdll_get(CDLinkedList* list, int index);
void* cdll_remove(CDLinkedList* list, int index);
int cdll_size(CDLinkedList* list);
Iterator* cdll_iterator(CDLinkedList* list);

#endif