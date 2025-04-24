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

int main() {
    BTree bst;
    tree_init(&bst);
    
    // 56 30 61 39 47 35 75 13 21 64 26 73 18
    tree_insert(&bst, 56);
    tree_insert(&bst, 30);
    tree_insert(&bst, 61);
    tree_insert(&bst, 39);
    tree_insert(&bst, 47);
    tree_insert(&bst, 35);
    tree_insert(&bst, 75);
    tree_insert(&bst, 13);
    tree_insert(&bst, 21);
    tree_insert(&bst, 64);
    tree_insert(&bst, 26);
    tree_insert(&bst, 73);
    tree_insert(&bst, 18);

    print_pre_order(bst._root);
}