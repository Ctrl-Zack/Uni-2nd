#include<bits/stdc++.h>
using namespace std;

typedef struct node_t {
    int value;
    int numberof;
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
    newNode->numberof = 1;
    newNode->_left = newNode->_right = NULL;
    return newNode;
}

Node *tree_search(Node *root, int target) {
    if(root == NULL || root->value == target) return root;
    if(root->value > target) return tree_search(root->_left, target);
    return tree_search(root->_right, target);
}

void tree_insert(BTree *tr, int value) {
    Node *sc = tree_search(tr->_root, value);
    if(sc == NULL) {
        tr->_root = _tree_insert(tr->_root, value);
        tr->_size++;
    } else {
        sc->numberof++; 
    }
}

Node *_tree_insert(Node *nd, int value) {
    if(nd == NULL) return create_new_node(value);
    if(nd->value > value) nd->_left = _tree_insert(nd->_left, value);
    if(nd->value < value) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

void tree_delete(BTree *tr, int target) {
    Node *sc = tree_search(tr->_root, target);
    if(sc != NULL) {
        if(sc->numberof == 1) {
            tr->_root = _tree_delete(tr->_root, target);
            tr->_size--;
        } else {
            sc->numberof--;
        }
    }
}

Node *_tree_delete(Node *root, int target) {
    if(root == NULL) return NULL;
    if(root->value > target) root->_left = _tree_delete(root->_left, target);
    else if(root->value < target) root->_right = _tree_delete(root->_right, target);
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


void print_pre_order(Node *root) {
    if(root == NULL) return;
    cout << root->value << "(" << root->numberof << ") ";
    print_pre_order(root->_left);
    print_pre_order(root->_right);
}

void print_in_order(Node *root) {
    if(root == NULL) return;
    print_in_order(root->_left);
    cout << root->value << "(" << root->numberof << ") ";
    print_in_order(root->_right);
}

void print_post_order(Node *root) {
    if(root == NULL) return;
    print_post_order(root->_left);
    print_post_order(root->_right);
    cout << root->value << "(" << root->numberof << ") ";
}

int main() {
    BTree bst;
    tree_init(&bst);
    
    int n, tmp;
    string command;
    cin >> n;
    while(n--) {
        cin >> command;
        if(command == "insert" || command == "remove") {
            cin >> tmp;
            if(command == "insert") tree_insert(&bst, tmp);
            else if(command == "remove") tree_delete(&bst, tmp);
        } else {
            if(command == "inorder") {
                print_in_order(bst._root);
                cout << "\n";
            } else if(command == "preorder") {
                print_pre_order(bst._root);
                cout << "\n";
            } else if(command == "postorder") {
                print_post_order(bst._root);
                cout << "\n";
            }
        }
    }
}