#include<bits/stdc++.h>
using namespace std;

typedef struct node_t {
    int value;
    struct node_t *_left, *_right;
} Node;

typedef struct btree_t {
    Node *_root;
    unsigned int _size;
} BTree;

vector<int> nodes;
bool isFound = 0;

Node *create_new_node(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->_left = newNode->_right = NULL;
    return newNode;
}

Node *tree_search(Node *root, int target, bool mode) {
    if(root == NULL) return root;
    if(mode) nodes.push_back(root->value);
    if(root->value == target) {
        isFound = 1;
        return root;
    }
    if(root->value > target) return tree_search(root->_left, target, mode);
    return tree_search(root->_right, target, mode);
}

Node *_tree_insert(Node *nd, int value) {
    if(nd == NULL) return create_new_node(value);
    if(nd->value > value) nd->_left = _tree_insert(nd->_left, value);
    if(nd->value < value) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

void tree_insert(BTree *tr, int value) {
    if(tree_search(tr->_root, value, 0) == NULL) {
        tr->_root = _tree_insert(tr->_root, value);
        tr->_size++;
    }
}


int main() {
    BTree bst;
    bst._root = NULL; bst._size = 0;
    
    int n, tmp;
    cin >> n;
    for (size_t i = 0; i < n; i++) {
        cin >> tmp;
        tree_insert(&bst, tmp);
    }

    cin >> tmp;
    tree_search(bst._root, tmp, 1);

    if(isFound) for(auto i: nodes) cout << i << " ";
    else cout << -1;
}