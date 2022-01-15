#ifndef QUEUE_H
#define QUEUE_H

#include "vec.h"

typedef struct Queue Queue;
Queue* queue();
void q_enqueue(Queue* queue, void* data);
void* q_dequeue(Queue* queue);
int q_size(Queue* queue);
void q_destroy(Queue* queue);
Iterator* q_iter(Queue* queue);

#endif