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

// * traversal functions

Node *pre_order_search(Node *root, int key) {
    if(root == NULL) return NULL;
    
    printf("%d -> ", root->value);
    if(root->value == key) return root;
    
    Node *left_res = pre_order_search(root->_left, key);
    if(left_res) return left_res;
    
    pre_order_search(root->_right, key);
}

Node *in_order_search(Node *root, int key) {
    if(root == NULL) return NULL;
    
    Node *left_res = in_order_search(root->_left, key);
    if(left_res) return left_res;
    
    printf("%d -> ", root->value);
    if(root->value == key) return root;
    
    in_order_search(root->_right, key);
}

Node *post_order_search(Node *root, int key) {
    if(root == NULL) return NULL;
    
    Node *left_res = post_order_search(root->_left, key);
    if(left_res) return left_res;
    
    Node *right_res = post_order_search(root->_right, key);
    if(right_res) return right_res;
    
    printf("%d -> ", root->value);
    if(root->value == key) return root;

    return NULL;
}

int main() {
    BTree bst;
    tree_init(&bst);
    
    printf("Enter the number of the nodes: ");
    int N;
    scanf("%d", &N);
    
    // * sample: 48 17 6 5 40 32 63 64 76 65 78
    printf("Nodes: ");
    for (size_t i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);
        tree_insert(&bst, tmp);
    }
    
    printf("Search key: ");
    int key_value;
    scanf("%d", &key_value);

    puts("\npre-order: ");
    Node *tmp = pre_order_search(bst._root, key_value);
    if(tmp) printf("\naddress: x%X | ans: %d\n", tmp, tmp->value);
    else printf("not found\n");
    
    puts("\nin-order: ");
    tmp = in_order_search(bst._root, key_value);
    if(tmp) printf("\naddress: x%X | ans: %d\n", tmp, tmp->value);
    else printf("not found\n");
    
    puts("\npost-order: ");
    tmp = post_order_search(bst._root, key_value);
    if(tmp) printf("\naddress: x%X | ans: %d\n", tmp, tmp->value);
    else printf("not found\n");
}