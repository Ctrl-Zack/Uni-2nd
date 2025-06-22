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

Node *create_new_node(int value) {
    Node *newNode = new Node;
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
            delete root;
            return NULL;
        } else if(root->_left == NULL || root->_right == NULL) {
            Node *tmp = (root->_left == NULL) ? root->_right : root->_left;
            delete root;
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

void print_pre_order(Node *root) {
    if(root == NULL) return;
    cout << root->value << " ";
    print_pre_order(root->_left);
    print_pre_order(root->_right);
}

void print_in_order(Node *root) {
    if(root == NULL) return;
    print_in_order(root->_left);
    cout << root->value << " ";
    print_in_order(root->_right);
}

void print_post_order(Node *root) {
    if(root == NULL) return;
    print_post_order(root->_left);
    print_post_order(root->_right);
    cout << root->value << " ";
}


int main() {
    multimap<string, int> color_node;
    BTree tr;
    tr._root = NULL; tr._size = 0;

    int val = 0;
    string color = "";
    while(val != -1 && color != "null") {
        cin >> val >> color;
        if(val != -1 && color != "null") {
            tree_insert(&tr, val);
            color_node.insert({color, val});
        }
    }

    cin >> color;
    for(auto i: color_node) if(i.first == color) tree_delete(&tr, i.second);

    cout << "Preorder : ";
    print_pre_order(tr._root);
    cout << "\nInorder : ";
    print_in_order(tr._root);
    cout << "\nPostorder : ";
    print_post_order(tr._root);

    return 0;
}