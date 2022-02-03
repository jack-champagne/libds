#include "bst.h"

typedef struct BSTNode {
    void* data;
    BSTNode* left;
    BSTNode* right;
} BSTNode;

struct BSTree {
    BSTNode* root;
    int size;
};

BSTree* bstree() {
    BSTree* new_tree = (BSTree*) malloc(sizeof(BSTree));
    new_tree->root = NULL;
    new_tree->size = 0;
}

BSTNode* bst_node(void* new_data) {
    BSTNode* new_node = (BSTNode*) malloc(sizeof(BSTNode));
    new_node->data = new_data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert(BSTree* bst, void* new_data) {
    if (bst->root == NULL) {
        bst->root = bst_node(new_data);
        bst->size = 1;
        return;
    }

    // Traverse, wait oh no. We need a comparison function.
}

char has(BSTree* bst, void* data_to_find) {

}

void* remove(BSTree* bst, void* data_to_remove) {

}

void bst_destroy(BSTree* bst) {

}
