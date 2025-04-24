/*
# Task
    draw the binary search tree (Bst) obtained for the following keys assuming they are inserted 
    in the order given: 56 30 61 39 47 35 75 13 21 64 26 73 18.
    there is one almost complete Bst for the previous keys. draw it.
    List the keys in an order that will produce the almost complete Bst
    assuming that the almost complete tree is stored in a one-dimensional array num[1..13], 
    write a recursive function for printing the integers in post-order.
#
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node_t {
    int value;
    struct node_t *_left, *_right;
} Node;

typedef struct btree_t {
    Node *_root;
    unsigned int _size;
} BTree;

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

Node *_tree_insert(Node *nd, int value) {
    if(nd == NULL) return create_new_node(value);
    if(nd->value > value) nd->_left = _tree_insert(nd->_left, value);
    if(nd->value < value) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

void tree_insert(BTree *tr, int value) {
    if(tree_search(tr->_root, value) == NULL) {
        tr->_root = _tree_insert(tr->_root, value);
        tr->_size++;
    }
}

void print_post_order(Node *root) {
    if(root == NULL) return;
    print_post_order(root->_left);
    print_post_order(root->_right);
    printf("%d > ", root->value);
}

void ins_to_complete(BTree *tr, int bst[], int lo, int hi) {
    if(lo <= hi) {
        int mid = (hi + lo) / 2;
        tree_insert(tr, bst[mid]);
        printf("%d ", bst[mid]);
        ins_to_complete(tr, bst, lo, mid - 1);
        ins_to_complete(tr, bst, mid + 1, hi);
    }
}

void ap_tree(BTree *tr, int bst[], int _SIZE) {
    for (int i = 0; i < _SIZE - 1; i++) {
        for (int j = 0; j < _SIZE - i - 1; j++) {
            if (bst[j] > bst[j + 1]) {
                int temp = bst[j];
                bst[j] = bst[j + 1];
                bst[j + 1] = temp;
            }
        }
    }
    ins_to_complete(tr, bst, 0, _SIZE - 1);
}

void array_representation(int bst[], Node *root, int idx) {
    if(root == NULL) return;
    bst[idx] = root->value;
    array_representation(bst, root->_left, idx * 2);
    array_representation(bst, root->_right, idx * 2 + 1);
}

int main() {
    BTree bst, b_tr;
    tree_init(&bst);
    tree_init(&b_tr);
    
    // * initial order: 56 30 61 39 47 35 75 13 21 64 26 73 18
    int arr[] = {56, 30, 61, 39, 47, 35, 75, 13, 21, 64, 26, 73, 18};
    int n = sizeof(arr) / sizeof(int);
    
    int BST_SIZE = (n == 0) ? 1 : 1U << (32 - __builtin_clz(n - 1)); // * get the nearest 2^n
    int arr_bst[BST_SIZE + 1];
    for (int i = 0; i <= BST_SIZE; i++) arr_bst[i] = -1;

    printf("Order before change\t: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        tree_insert(&bst, arr[i]);
    }

    printf("\nPost-Order before\t: ");
    print_post_order(bst._root);
    
    // * notice that it doesnt create an almost complete bst
    
    /*
    * here is the visualization:
    *                       56
    *                     /    \
    *                   30       61  
    *                 /    \        \
    *               13      39        75
    *                 \    /   \     /
    *                 21  35   47   64
    *                 / \             \
    *                18  26            73
    */
   
    // * to make an almost complete tree we have to do some adjustment to the order of the elements of the tree
    printf("\nOrder after change\t: ");
    ap_tree(&b_tr, arr, n);
    // * the order after: 39 21 13 18 30 26 35 61 47 56 73 64 75
    
    printf("\nPost-Order after\t: ");
    print_post_order(b_tr._root);
    
    /*
    * here is the visualization:
    *                      39(1)
    *                    /    \
    *                   /      \
    *                 21(2)      61(3) 
    *                /  \       /  \
    *               /    \     /    \  
    *            13(4) 30(5) 47(6)  73(7)
    *              \    / \    \    / \
    *              18  26 35    56 64  75
    *            (8) (9) (10) (11) (12) (13) 
    */
   
    array_representation(arr_bst, b_tr._root, 1);
    printf("\nArray representation\t: "); // * -1 means that it is a NULL node
    for (int i = 1; i <= BST_SIZE; i++) {
        printf("%d ", arr_bst[i]);
    }
}