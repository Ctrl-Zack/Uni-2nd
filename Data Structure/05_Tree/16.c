/*
# Task
    store the following integers in an array bst[1..15] such that bst represents a complete 
    binary search tree: 34 23 45 46 37 78 90 2 40 20 87 53 12 15 91.
*/

#include<stdio.h>
#include<stdlib.h>

// * binary tree data structure

typedef struct node_t {
    int value;
    struct node_t *_left, *_right;
} Node;

Node *create_new_node(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->_left = newNode->_right = NULL;
    return newNode;
}

Node *tree_search(Node *root, int target) {
    if(root == NULL || root->value == target) return root;
    if(root->value > target) return tree_search(root->_left, target);
    return tree_search(root->_right, target);
}

Node *_tree_insert(Node *nd, int value) {
    if(nd == NULL) return create_new_node(value);
    if(nd->value > value) nd->_left = _tree_insert(nd->_left, value);
    if(nd->value < value) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

Node *tree_insert(Node *root, int value) {
    if(tree_search(root, value) == NULL) root = _tree_insert(root, value);
    return root;
}

// * ANSWER:

void print_pre_order(Node *root) {
    if(root == NULL) return;
    printf("%d -> ", root->value);
    print_pre_order(root->_left);
    print_pre_order(root->_right);
}

void ins_to_complete(Node **tr, int bst[], int lo, int hi) {
    // * this function act like a binary search, but instead of searching for an element, it's inserting it to the bst
    if(lo <= hi) {
        int md = (hi + lo) / 2;
        *tr = tree_insert(*tr, bst[md]);
        printf("inserting: %d\n", bst[md]);
        ins_to_complete(tr, bst, lo, md - 1);
        ins_to_complete(tr, bst, md + 1, hi);
    }
}

int main() {
    Node *complete = NULL;

    // * the answer should be
    // * 40 20 12 2 15 34 23 37 78 46 45 53 90 87 91
    // * meanwhile the array is: 
    int bst[] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91};
    int n = sizeof(bst) / sizeof(int);
    
    // * so the first thing that we should do is to sort the array    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bst[j] > bst[j + 1]) {
                int temp = bst[j];
                bst[j] = bst[j + 1];
                bst[j + 1] = temp;
            }
        }
    }
    // * 2 12 15 20 23 34 37 40 45 46 53 78 87 90 91
    // * after that we call this function to make the bst
    ins_to_complete(&complete, bst, 0, n - 1);
    printf("Pre-Order traversal: ");
    print_pre_order(complete);
    /*
    * here is the visualization:
    *                     40(1)
    *                    /    \
    *                   /      \
    *               20(2)       78(3) 
    *               /  \         /  \
    *              /    \       /    \  
    *           12(4)  34(5)   46(6)  90(6)
    *           / \    / \     / \    / \
    *          2  15  23 37   45 53  87  91
    *        (7) (8) (9)(10) (11)(12)(13)(14) 
    */
}