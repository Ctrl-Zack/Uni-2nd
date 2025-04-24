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

typedef struct btree_t {
    Node *_root;
    unsigned int _size;
} BTree;

void tree_init(BTree *tr);
Node *create_new_node(int value);
Node *tree_search(Node *root, int target);
void tree_insert(BTree *tr, int value);
Node *_tree_insert(Node *nd, int value);
void tree_delete(BTree *tr, int target);
Node *_tree_delete(Node *root, int target);
Node *__tree_find_min(Node *root);


void tree_init(BTree *tr) {
    tr->_root = NULL;
    tr->_size =0;
}

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

void tree_insert(BTree *tr, int value) {
    if(tree_search(tr->_root, value) == NULL) {
        tr->_root = _tree_insert(tr->_root, value);
        tr->_size++;
    }
}

Node *_tree_insert(Node *nd, int value) {
    if(nd == NULL) return create_new_node(value);
    if(nd->value > value) nd->_left = _tree_insert(nd->_left, value);
    if(nd->value < value) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

void tree_delete(BTree *tr, int target) {
    if(tree_search(tr->_root, target) != NULL) {
        tr->_root = _tree_delete(tr->_root, target);
        tr->_size--;
    }
}

Node *_tree_delete(Node *root, int target) {
    if(root == NULL) return NULL;
    if(root->value > target) root->_left = _tree_delete(root->_left, target);
    if(root->value < target) root->_right = _tree_delete(root->_right, target);
    else {
        if(root->_left == NULL && root->_right == NULL) {
            free(root);
            return NULL;
        } else if(root->_left == NULL || root->_right == NULL) {
            Node *tmp = (root->_left == NULL) ? root->_right : root->_left;
            free(root);
            return tmp; 
        } else {
            Node *tmp = __tree_find_min(root->_right);
            root->value = tmp->value;
            root->_right = _tree_delete(root->_right, tmp->value);
        }
    }
    return root;
}

Node *__tree_find_min(Node *root) {
    if(root == NULL) return NULL;
    else if(root->_left != NULL) return __tree_find_min(root->_left);
    return root;
}

// * traversal functions

void print_pre_order(Node *root) {
    if(root == NULL) return;
    printf("%d -> ", root->value);
    print_pre_order(root->_left);
    print_pre_order(root->_right);
}

void print_in_order(Node *root) {
    if(root == NULL) return;
    print_pre_order(root->_left);
    printf("%d -> ", root->value);
    print_pre_order(root->_right);
}

void print_post_order(Node *root) {
    if(root == NULL) return;
    print_pre_order(root->_left);
    print_pre_order(root->_right);
    printf("%d -> ", root->value);
}

void ins_to_complete(BTree *tr, int bst[], int lo, int hi) {
    if(lo <= hi) {
        int mid = (hi + lo) / 2;
        tree_insert(tr, bst[mid]);
        printf("inserting: %d\n", bst[mid]);
        ins_to_complete(tr, bst, lo, mid - 1);
        ins_to_complete(tr, bst, mid + 1, hi);
    }
}

int main() {
    BTree complete;
    tree_init(&complete);

    int bst[] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91};
    int n = sizeof(bst) / sizeof(int);
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bst[j] > bst[j + 1]) {
                int temp = bst[j];
                bst[j] = bst[j + 1];
                bst[j + 1] = temp;
            }
        }
    }

    ins_to_complete(&complete, bst, 0, n - 1);
    
    print_pre_order(complete._root);
}