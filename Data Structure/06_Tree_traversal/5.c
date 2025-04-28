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

void tree_init(BTree *tr);
Node *create_new_node(int value);
Node *tree_search(Node *root, int target);
void tree_insert(BTree *tr, int value);
Node *_tree_insert(Node *nd, int value);

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
    if(!root || root->value == target) return root;
    if(root->value > target) return tree_search(root->_left, target);
    return tree_search(root->_right, target);
}

void tree_insert(BTree *tr, int value) {
    if(!tree_search(tr->_root, value)) {
        tr->_root = _tree_insert(tr->_root, value);
        tr->_size++;
    }
}

Node *_tree_insert(Node *nd, int value) {
    if(!nd) return create_new_node(value);
    if(nd->value > value) nd->_left = _tree_insert(nd->_left, value);
    if(nd->value < value) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

// * traversal functions
void print_in_order(Node *root) {
    if(!root) return;
    print_in_order(root->_left);
    printf("%d, ", root->value);
    print_in_order(root->_right);
}

void print_pre_order(Node *root) {
    if(root == NULL) return;
    printf("%d, ", root->value);
    print_pre_order(root->_left);
    print_pre_order(root->_right);
}


// * replace root by its successor or predecessor
Node *replace_root_with_successor(BTree *tr) {
    if(!tr->_root) return NULL;
    
    if(!tr->_root->_left && !tr->_root->_right) {
        free(tr->_root);
        return NULL;
    }
    
    if(!tr->_root->_left){
        Node *tmp = tr->_root;
        tr->_root = tr->_root->_right;
        free(tmp);
        return tr->_root;
    }
    
    if(!tr->_root->_right) {
        Node *tmp = tr->_root;
        tr->_root = tr->_root->_left;
        free(tmp);
        return tr->_root;
    }

    Node *p_successor = tr->_root;
    Node *successor = p_successor->_right;

    while (successor->_left) {
        p_successor = successor;
        successor = successor->_left;
    }
    
    tr->_root->value = successor->value;

    if(p_successor == tr->_root) p_successor->_right = successor->_right;
    else p_successor->_left = successor->_right;

    free(successor);
    return tr->_root;
}

Node *replace_root_with_predecessor(BTree *tr) {
    if(!tr->_root) return NULL;
    
    if(!tr->_root->_left && !tr->_root->_right) {
        free(tr->_root);
        return NULL;
    }
    
    if(!tr->_root->_left){
        Node *tmp = tr->_root;
        tr->_root = tr->_root->_right;
        free(tmp);
        return tr->_root;
    }
    
    if(!tr->_root->_right) {
        Node *tmp = tr->_root;
        tr->_root = tr->_root->_left;
        free(tmp);
        return tr->_root;
    }

    Node *p_predecessor = tr->_root;
    Node *predecessor = p_predecessor->_left;

    while (predecessor->_right) {
        p_predecessor = predecessor;
        predecessor = predecessor->_right;
    }
    
    tr->_root->value = predecessor->value;

    if(p_predecessor == tr->_root) p_predecessor->_left = predecessor->_left;
    else p_predecessor->_right = predecessor->_left;

    free(predecessor);
    return tr->_root;
}

int main() {
    BTree bst1, bst2;
    tree_init(&bst1);
    tree_init(&bst2);
    
    printf("Enter the number of the nodes: ");
    int N;
    scanf("%d", &N);
    
    // * sample: 48 17 6 5 40 32 63 64 76 65 78
    printf("Nodes: ");
    for (size_t i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);
        tree_insert(&bst1, tmp);
        tree_insert(&bst2, tmp);
    }
    
    puts("(i) replace root by its in-order successor");
    puts("before replacing: ");
    printf("in-order traversal: ");
    print_in_order(bst1._root); printf("\n");
    printf("pre-order traversal: ");
    print_pre_order(bst1._root); printf("\n");
    replace_root_with_successor(&bst1);
    puts("after replacing: ");
    printf("in-order traversal: ");
    print_in_order(bst1._root); printf("\n");
    printf("pre-order traversal: ");
    print_pre_order(bst1._root); printf("\n\n");
    
    puts("(ii) replace root by its in-order predecessor");
    puts("before replacing: ");
    printf("in-order traversal: ");
    print_in_order(bst2._root); printf("\n");
    printf("pre-order traversal: ");
    print_pre_order(bst2._root); printf("\n");
    replace_root_with_predecessor(&bst2);
    puts("after replacing: ");
    printf("in-order traversal: ");
    print_in_order(bst2._root); printf("\n");
    printf("pre-order traversal: ");
    print_pre_order(bst2._root); printf("\n");
}