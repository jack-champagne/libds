#ifndef STACK_H
#define STACK_H

#include "vec.h"

typedef struct Stack Stack;

Stack* stack();
void stk_push(Stack* stack, void* data);
void* stk_pop(Stack* stack);
int stk_size(Stack* stack);
void stk_destroy(Stack* stack);
Iterator* stk_iterator(Stack* stack);

#endif