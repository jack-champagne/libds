#ifndef DLNODE_H
#define DLNODE_H 

typedef struct DLNode {
    void* data;
    struct DLNode* next;
    struct DLNode* prev;
} DLNode;

#endif