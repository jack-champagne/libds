#include "stack.h"

struct Stack {
    LinkedList* stack_list;
};

Stack* stack() {
    Stack* ret_stack = (Stack*) malloc(sizeof(Stack));
    ret_stack->stack_list = linked_list();
    return ret_stack;
}

void stk_push(Stack* stack, void* data) {
    ll_prepend(stack->stack_list, data);
}

void* stk_pop(Stack* stack) {
    return ll_remove(stack->stack_list, 0);
}

int stk_size(Stack* stack) {
    return ll_size(stack->stack_list);
}

void stk_destroy(Stack* stack) {
    ll_destroy(stack->stack_list);
    free(stack);
}

Iterator* stk_iterator(Stack* stack) {
    return ll_iterator(stack->stack_list);
}