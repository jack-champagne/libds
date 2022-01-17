#include "iterator.h"

#include "node.h"

struct Iterator {
    struct Node* current;
};

/// Sets the internal parameters of an Iterator struct
/// so that it is initialized to the correct starting location.
/// Usage:
/// Iterator* ret_iter = (Iterator*) malloc(sizeof(Iterator));
/// iterator(new_iter, list->head);
Iterator* iterator(void* init_node) {
    Iterator* new_iter = (Iterator*) malloc(sizeof(Iterator));
    new_iter->current = (struct Node*) init_node;
    return new_iter;
}

/// Retrieves next data pointer if it exists and
/// returns NULL if next data does not exist or iterator is NULL itself
/// Usage:
/// Iterator* my_iter = iterator(my_linked_list);
/// while ((void* data = iter_next(my_iter)) != NULL) { printf("%d", data) }
void* iter_next(Iterator* iterator) {
    if (iterator == NULL || iterator->current == NULL) {
        return NULL;
    }
    void* ret = iterator->current->data;
    iterator->current = iterator->current->next;
    return ret;
}


/// Deallocates iterator and information stored by it
/// Usage:
/// iter_destroy(my_iter);
/// Returns void
void iter_destroy(Iterator* iterator) {
    free(iterator);
}