#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdlib.h>
#include "node.h"

typedef struct Iterator {
    Node* current;
} Iterator;

void* iter_next(Iterator* iterator);
void iter_destroy(Iterator* iterator);

#endif