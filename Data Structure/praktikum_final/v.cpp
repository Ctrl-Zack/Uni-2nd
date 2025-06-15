#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

struct Node {
    int value;
    struct Node *_left, *_right;
};

struct BTree {
    Node *_root;
    unsigned int _size;
};

void tree_init(BTree *tr) {
    tr->_root = NULL;
    tr->_size = 0;
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

Node *__tree_find_min(Node *root) {
    if(root == NULL) return NULL;
    else if(root->_left != NULL) return __tree_find_min(root->_left);
    return root;
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

void tree_delete(BTree *tr, int target) {
    if(tree_search(tr->_root, target) != NULL) {
        tr->_root = _tree_delete(tr->_root, target);
        tr->_size--;
    }
}


void print_in_order(Node *root) {
    if(root == NULL) return;
    print_in_order(root->_left);
    cout << root->value << " ";
    print_in_order(root->_right);
}

Node *depth_search(Node *root, int target, int &depth) {
    if(root == NULL || root->value == target) return root;
    depth++;
    if(root->value > target) return depth_search(root->_left, target, depth);
    else if(root->value < target) return depth_search(root->_right, target, depth);
    return NULL;
}

int main() {
    BTree bst;
    tree_init(&bst);
    string cmd;
    int n, tmp;
    cin >> n;

    while(n--) {
        cin >> cmd;
        if(cmd == "PRINT") {
            if(bst._root == NULL) cout << "EMPTY\n";
            else {
                print_in_order(bst._root);
                cout << '\n';
            }
        } else {
            cin >> tmp;

            if(cmd == "INSERT") tree_insert(&bst, tmp);
            else if(cmd == "DELETE") tree_delete(&bst, tmp);
            else if(cmd == "SEARCH") {
                int depth = 1;
                if (depth_search(bst._root, tmp, depth) != NULL)
                    cout << depth << '\n';
                else cout << -1 << '\n';
            }
        }
    }
}