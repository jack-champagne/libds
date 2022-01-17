#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdlib.h>

typedef struct Iterator Iterator;

Iterator* iterator(void* init_node);
void* iter_next(Iterator* iterator);
void iter_destroy(Iterator* iterator);

#endif