#include "vec.h"

struct LinkedList {
    Node* head;
    int size;
    Node* tail; 
};

Node* ll_node(void* new_data) {
    Node* ret = (Node*) malloc(sizeof(Node));
    ret->data = new_data;
    ret->next = NULL;
    return ret;
}

/// Get node at index. Not for outside use. For library use only.
/// Usage:
/// Node* node_at_index = ll_get(my_list, 1); // Returns the second node in the list if it exists
/// Returns Node* to node struct rep. index i.
Node* get_node(LinkedList* list, int index) {
    if (index >= list->size || index < 0) {
        return NULL;
    }

    Node* ret = list->head;
    int i = 0;
    while (ret != NULL && i < index) {
        ret = ret->next;
        i++;
    }

    return ret;
}

/// Mallocs a new linked list struct and initializes fields.
/// Usage:
/// LinkedList* my_list = linked_list();
/// 
/// Returns pointer to dynamically allocated linked list
LinkedList* linked_list() {
    LinkedList* ret = (LinkedList*) malloc(sizeof(LinkedList));
    ret->size = 0;
    ret->head = NULL;
    ret->tail = NULL;

    return ret;
}

/// Deallocs the list, and all nodes contained
/// It is the library user's responsibility to dealloc the data.
/// Usage:
/// ll_destroy(my_list);
///
/// Returns void
void ll_destroy(LinkedList* list) {
    while (list->head != NULL) {
        Node* next = list->head->next;
        free(list->head);
        list->head = next;
    }
    free(list);
}

/// Append takes malloc'd data and dynamically allocates space on the heap
/// for the new node. This is necessary because we cannot know for sure if
/// the library user will malloc and free properly.
/// Usage example:
/// append(my_list, data_to_append);
/// 
/// Returns void
void ll_append(LinkedList* list, void* data_to_append) {
    if (list == NULL || data_to_append == NULL) {
        fprintf(stderr, "list or data pointer is null\n");
    }
    // Handle case where list head is null (no elements)
    if (list->head == NULL) {
        list->head = ll_node(data_to_append);
        list->tail = list->head;
        list->size = 1;
    } else {
        Node* new_node = ll_node(data_to_append);
        list->tail->next = new_node;
        list->tail = new_node;
        list->size++;
    }
}

/// Inserts node after the node given and manages pointers properly. Assume node
/// to insert is a new node that is not currently in the list.
/// Special case: if prev is NULL, insert node at head.
/// Usage:
/// ll_insert_after(my_list, predecessor_node, new_node);
///
/// Returns void
void ll_insert_at(LinkedList* list, int index, void* data_to_insert) {
    if (list == NULL || data_to_insert == NULL) {
        fprintf(stderr, "list or data_to_insert NULL, cannot insert after\n");
        return;
    }

    // Design choice: Originally, this implementation for insert_after did not
    // include a LinkedList* list parameter because insertion of a node only requires
    // the proper swapping of references. This was changed to allow the list->size
    // parameter to remain updated.
    Node* new_node = ll_node(data_to_insert);
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->size = 1;
        return;
    }

    Node* prev = get_node(list, index - 1);
    Node* successor = get_node(list, index);
    if (prev == NULL) {
        successor = list->head;
        list->head = new_node;

    } else {
        if (prev == list->tail) {
            list->tail = new_node;
        }
        successor = prev->next;
        prev->next = new_node;
    }

    new_node->next = successor;
    list->size++;
}

/// Prepend data to beginning of list (the head)
/// Usage:
/// ll_prepend(my_list, data_to_prepend)
void ll_prepend(LinkedList* list, void* data_to_prepend) {
    ll_insert_at(list, 0, data_to_prepend);
}

/// Returns the data at specified index in linked list (or NULL)
/// Usage:
/// printf("%d", *(int*)ll_get(my_list, 1)); // Prints second element in my_list if it exists.
/// Runtime: O(n)
void* ll_get(LinkedList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        fprintf(stderr, "list null or index out of bounds\n");
        return NULL;
    }

    return get_node(list, index)->data;
}

/// Removes node at specified index
/// Usage:
/// int* data = ll_remove(my_list, 1); // Removes and returns pointer to data of the second element of list if element exists
/// Runtime: O(n) (when we traverse), O(1) when removing head
void* ll_remove(LinkedList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        fprintf(stderr, "list null or index out of bounds\n");
        return NULL;
    }

    Node* removed_node;
    Node* prev = get_node(list, index - 1);
    if (index == 0) {
        // Change head
        removed_node = list->head;
        list->head = removed_node->next;
    } else {
        // Repair list
        removed_node = get_node(list, index);
        prev->next = removed_node->next;
    }

    // Fix tail pointer if needed
    if (removed_node == list->tail) {
        list->tail = prev;
    }
    list->size--;

    void* ret = removed_node->data;
    free(removed_node);
    return ret;
}

/// Check to see if list is empty
/// Usage:
/// if (ll_is_empty(my_list)) { foo(); }
///
/// Returns 1 if empty, 0 if not empty.
int ll_is_empty(LinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, "list pointer null\n");
    }
    return (list->size == 0);
}

/// Returns iterator struct for easy enumeration of elements
/// Usage:
/// Iterator* my_iter = ll_iterator(my_list);
Iterator* ll_iterator(LinkedList* list) {
    Iterator* ret_iter = iterator(list->head);
    return ret_iter;
}

/// Returns size of linked list in number of nodes
/// Usage:
/// int length = ll_size(my_list);
int ll_size(LinkedList* list) {
    return list->size;
}