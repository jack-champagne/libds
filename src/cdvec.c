#include "cdvec.h"

#include "dlnode.h"

struct CDLinkedList {
    struct DLNode* last; // NOTE: head is next of last.
    int size;
};

struct DLNode* cdll_node(void* new_data) {
    struct DLNode* ret = (struct DLNode*) malloc(sizeof(struct DLNode));
    ret->data = new_data;
    ret->prev = NULL;
    ret->next = NULL;
    return ret;
}

/// Get node at index. Not for outside use. For library use only.
/// Usage (*NOT USED OUTSIDE LIBRARY*):
/// DLNode* node_at_index = ll_get(my_list, 1); // Returns the second node in the list if it exists
/// Returns Node* to node struct rep. index i.
struct DLNode* cdll_get_node(CDLinkedList* list, int index) {
    if (index >= list->size || index < 0) {
        return NULL;
    }

    struct DLNode* ret = list->last->next;
    int i = 0;
    while (ret != NULL && i < index) { // IS this null check necessary?
        ret = ret->next;
        i++;
    }

    return ret;
}

/// Mallocs a new circular doubly linked list struct and initializes fields.
/// Usage:
/// CDLinkedList* my_list = cdlinkedlist();
/// 
/// Returns pointer to dynamically allocated linked list
CDLinkedList* cdlinkedlist() {
    CDLinkedList* ret = (CDLinkedList*) malloc(sizeof(CDLinkedList));
    ret->size = 0;
    ret->last = NULL;

    return ret;
}

/// Deallocs the list, and all nodes contained
/// It is the library user's responsibility to dealloc the data.
/// Usage:
/// ll_destroy(my_list);
///
/// Returns void
void cdll_destroy(CDLinkedList* list) {
    if (list->last != NULL) {
        struct DLNode* cur = list->last->next; // HEAD
        while (cur != list->last) {
            struct DLNode* free_node = cur;
            cur = cur->next;
            free(free_node);
        }
        free(list->last);
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
void cdll_append(CDLinkedList* list, void* data_to_append) {
    if (list == NULL || data_to_append == NULL) {
        fprintf(stderr, "list or data pointer is null\n");
    }
    // Handle case where list empty (no elements)
    if (list->last == NULL) {
        list->last = cdll_node(data_to_append);
        list->last->next = list->last;
        list->last->prev = list->last;
        list->size = 1;
    } else {
        struct DLNode* new_node = cdll_node(data_to_append); // TODO: Remove this line
        DLNode* old_head = list->last->next;

        list->last->next = new_node;
        new_node->prev = list->last;
        list->last = new_node;
        new_node->next = old_head;
        old_head->prev = list->last;
        list->size++;

    }
}

// TODO: Remake to use previous method and move list->last accrordingly. Do a temp store.

/// Inserts node after the node given and manages pointers properly. Assume node
/// to insert is a new node that is not currently in the list.
/// Special case: if prev is NULL, insert node at head.
/// Usage:
/// ll_insert_after(my_list, predecessor_node, new_node);
///
/// Returns void
void cdll_insert_at(CDLinkedList* list, int index, void* data_to_insert) {
    if (list == NULL || data_to_insert == NULL) {
        fprintf(stderr, "list or data_to_insert NULL, cannot insert after\n");
        return;
    }

    // TODO: Account for user being stupid and inserting at last index.
    
    // Design choice: Originally, this implementation for insert_after did not
    // include a LinkedList* list parameter because insertion of a node only requires
    // the proper swapping of references. This was changed to allow the list->size
    // parameter to remain updated.
    struct DLNode* new_node = cdll_node(data_to_insert);
    if (list->last == NULL) {
        list->last = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        list->size = 1;
        return;
    }

    struct DLNode* successor = list->last->next; // Starts at head.
    for (int i = 0; i < index; i++) {
        successor = successor->next;
    }
    successor->prev->next = new_node;
    new_node->prev = successor->prev;
    new_node->next = successor;
    successor->prev = new_node;

    if (index == list->size) {
        list->last = new_node;
    }
    // TODO: Remove repeated code (see line 118 in function.)

    list->size++;
}

/// Prepend data to beginning of list (the head)
/// Usage:
/// ll_prepend(my_list, data_to_prepend)
void cdll_prepend(CDLinkedList* list, void* data_to_prepend) {
    cdll_insert_at(list, 0, data_to_prepend);
}

/// Returns the data at specified index in linked list (or NULL)
/// Usage:
/// printf("%d", *(int*)ll_get(my_list, 1)); // Prints second element in my_list if it exists.
/// Runtime: O(n)
void* cdll_get(CDLinkedList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        fprintf(stderr, "list null or index out of bounds\n");
        return NULL;
    }

    return cdll_get_node(list, index)->data;
}

/// Removes node at specified index
/// Usage:
/// int* data = ll_remove(my_list, 1); // Removes and returns pointer to data of the second element of list if element exists
/// Runtime: O(n) (when we traverse), O(1) when removing head
void* cdll_remove(CDLinkedList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        fprintf(stderr, "list null or index out of bounds\n");
        return NULL;
    }

    struct DLNode* removed_node = cdll_get_node(list, index);
    struct DLNode* prev_node = removed_node->prev;
    struct DLNode* next_node = removed_node->next;
    void* ret;

    if (index == list->size - 1) {
        if (list->last->prev == list->last) {
            list->last = NULL;
        } else {
            list->last = list->last->prev;
        }
    }

    prev_node->next = next_node;
    next_node->prev = prev_node;
    list->size--;
 
    ret = removed_node->data;
    free(removed_node);
    return ret;
}

/// Check to see if list is empty
/// Usage:
/// if (ll_is_empty(my_list)) { foo(); }
///
/// Returns 1 if empty, 0 if not empty.
int cdll_is_empty(CDLinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, "list pointer null\n");
    }
    return (list->size == 0);
}

/// Returns iterator struct for easy enumeration of elements
/// Usage:
/// Iterator* my_iter = ll_iterator(my_list);
Iterator* cdll_iterator(CDLinkedList* list) {
    //Iterator* ret_iter = iterator(list->last->next);
    return NULL;
}

/// Returns size of linked list in number of nodes
/// Usage:
/// int length = ll_size(my_list);
int cdll_size(CDLinkedList* list) {
    return list->size;
}