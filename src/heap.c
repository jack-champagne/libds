#include "heap.h"

struct HElement {
    void* data;
    char marked;
};

// Useful definitions:
// rank = # of direct children of node 

void fh_insert(void* data) {
    // Create new singleton tree
    // Add to root list
    // Update min-pointer if necessary
}

void* fh_delete_min() {
    // Delete min (store in ret var)
    // meld children into *root* list
    // Update min if necessary
    // Consolidate trees so that no two root have same rank
}

void decrease_key() {
    
}