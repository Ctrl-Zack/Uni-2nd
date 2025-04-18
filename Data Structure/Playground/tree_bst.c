#include<stdio.h>
#include<stdlib.h>

typedef struct bstnode_t {
    int key;
    struct bstnode_t \
    *left,
    *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;



int main() {
    return 0;
}