#include "queue.h"

struct Queue {
    LinkedList* queue_list;
};

/// Initializes and returns a new queue datastructure that the
/// functions of this file can act upon. 
/// Usage:
/// Queue* my_queue = queue();
Queue* queue() {
    Queue* ret_queue = (Queue*) malloc(sizeof(Queue));
    ret_queue->queue_list = linkedlist();
    return ret_queue;
}

/// Puts an element into the end of the queue.
/// Usage:
/// char* my_str = (char*) malloc(sizeof(char) * 20);
/// strcpy(my_str, "Hello world!");
/// Queue* my_queue = queue();
/// q_enqueue(my_queue, my_str);
void q_enqueue(Queue* queue, void* data) {
    ll_append(queue->queue_list, data);
}

/// Removes and returns the first item of the queue.
/// Usage:
/// Queue* my_queue = queue();
/// q_enqueue(my_queue, my_str);
/// printf("%s", (char*) q_dequeue(my_queue))
void* q_dequeue(Queue* queue) {
    return ll_remove(queue->queue_list, 0);
}

/// Returns size of queue
/// Usage:
/// int length = q_size(my_queue);
int q_size(Queue* queue) {
    return ll_size(queue->queue_list);
}

/// Returns iterable struct for queue to
/// iterate from start of queue to the end
/// This does not dequeue any elements and
/// only allows iterable access to the elements
/// of the queue.
/// Usage:
/// int* data;
/// while ((data = dequeue(my_queue)) != NULL) {
////    printf("%d", *data);
/// }
Iterator* q_iterator(Queue* queue) {
    return ll_iterator(queue->queue_list);
}

/// Deallocs resources for queue
/// It is the library users responsibility to dealloc
/// the data
/// Usage:
/// q_destroy(my_queue);
void q_destroy(Queue* queue) {
    ll_destroy(queue->queue_list);
    free(queue);
}