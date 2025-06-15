#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int value;
    struct Node *_left, *_right;
};

struct BTree {
    Node *_root;
    unsigned int _size;
};

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

void print_pre_order(Node *root, vector<int> &ls, int &idx, bool &ans) {
    if(root == NULL) return;
    // cout <<  root->value << endl;
    if(ls[idx++] != root->value) {
        ans = 0;
        return;
    }
    print_pre_order(root->_left, ls, idx, ans);
    print_pre_order(root->_right, ls, idx, ans);
}

int main() {
    BTree bst;
    tree_init(&bst);
    
    int N, idx = 0;
    bool ans = 1;
    cin >> N;
    vector<int> ls(N);
    for(int i = 0; i < N; i++) {
        cin >> ls[i];
        tree_insert(&bst, ls[i]);
    }

    print_pre_order(bst._root, ls, idx, ans);

    if(ans) cout << "Ini pohon";
    else cout << "Ini bukan pohon";
}