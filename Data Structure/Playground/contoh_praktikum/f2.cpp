#include<bits/stdc++.h>
using namespace std;

typedef struct AVLNode_t {
    int data;
    struct AVLNode_t *left, *right;
    int height;
} AVLNode;

typedef struct AVL_t {
    AVLNode *_root;
    unsigned int _size;
} AVL;

bool same = 1;

AVLNode *_avl_createNode(int value) {
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode *_search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data) root = root->left;
        else if (value > root->data) root = root->right;
        else return root;
    }
    return root;
}

int _getHeight(AVLNode *node) {
    if(node == NULL) return 0; 
    return node->height;
}

int _max(int a, int b) {
    return (a > b) ? a : b;
}

int _getBalanceFactor(AVLNode *node){
    if(node == NULL) return 0;
    return _getHeight(node->left) - _getHeight(node->right);
}

AVLNode *_insert_AVL(AVL *avl, AVLNode *node, int value) {
    
    if(node == NULL) return _avl_createNode(value);
    if(value < node->data) node->left = _insert_AVL(avl, node->left, value);
    else if(value > node->data) node->right = _insert_AVL(avl, node->right, value);
    
    node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right)); 

    int balanceFactor = _getBalanceFactor(node);
    
    if((balanceFactor > 1 && value < node->left->data) || (balanceFactor > 1 && value > node->left->data) || (balanceFactor < -1 && value > node->right->data) || (balanceFactor < -1 && value < node->right->data)) {
        same = 0;
    }
    
    return node;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL) return false;
    
    if (temp->data == value) return true;
    else return false;
}

void avl_insert(AVL *avl, int value){
    if(!avl_find(avl, value)){
        avl->_root = _insert_AVL(avl, avl->_root, value);
        avl->_size++;
    }
}

int main(){
    AVL tr;
    tr._root = NULL; tr._size = 0;
    
    int n, tmp;
    cin >> n;
    while(n--) {
        cin >> tmp;
        if(same) avl_insert(&tr, tmp);
    }

    if(same) cout << "Sama Cuy!";
    else cout << "Kecewa Berat";

}