#include <bits/stdc++.h> 
using namespace std; 

struct Node { 
    int key; 
    Node *left; 
    Node *right; 
    int height; 

    Node(int k) { 
        key = k; 
        left = right = nullptr; 
        height = 1; 
    }
}; 

int height(Node *N) { 
    if (N == nullptr) 
        return 0; 
    return N->height; 
} 

Node *rightRotate(Node *y) { 
    Node *x = y->left; 
    Node *T2 = x->right; 

    x->right = y; 
    y->left = T2; 

    y->height = 1 + max(height(y->left), height(y->right)); 
    x->height = 1 + max(height(x->left), height(x->right)); 

    return x; 
} 

Node *leftRotate(Node *x) { 
    Node *y = x->right; 
    Node *T2 = y->left; 

    y->left = x; 
    x->right = T2; 

    x->height = 1 + max(height(x->left), height(x->right)); 
    y->height = 1 + max(height(y->left), height(y->right)); 

    return y; 
} 

int getBalance(Node *N) { 
    if (N == nullptr) 
        return 0; 
    return height(N->left) - height(N->right); 
} 

Node* insert(Node* node, int key) { 
    if (node == nullptr) 
        return new Node(key); 

    if (key < node->key) 
        node->left = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else
        return node; 

    node->height = 1 + max(height(node->left), height(node->right)); 

    int balance = getBalance(node); 

    if (balance > 1 && key < node->left->key) {
        cout << "Left Case"
            << "\nPivotNode: " << node->key
            << "\nPivotNode->left: "  << node->left->key
            << "\nPivotNode->left->left: " << node->left->left->key
            << "\n\n";

        cout << "result:" 
            << "\nNewNode: " << node->left->key
            << "\nNewNode->left: " << node->left->left->key
            << "\nNewNode->right: " << node->key
            << "\n\n";

        return rightRotate(node); 
    }

    if (balance < -1 && key > node->right->key) {
        cout << "Right Case"
            << "\nPivotNode: " << node->key
            << "\nPivotNode->right: "  << node->right->key
            << "\nPivotNode->right->right: " << node->right->right->key
            << "\n\n";

        cout << "result:" 
            << "\nNewNode: " << node->right->key
            << "\nNewNode->left: " << node->key
            << "\nNewNode->right: " << node->right->right->key
            << "\n\n";

        return leftRotate(node); 
    }

    if (balance > 1 && key > node->left->key) { 
        cout << "Left Right Case"
            << "\nPivotNode: " << node->key
            << "\nPivotNode->left: "  << node->left->key
            << "\nPivotNode->left->right: " << node->left->right->key
            << "\n\n";

        cout << "result:" 
            << "\nNewNode: " << node->left->right->key
            << "\nNewNode->left: " << node->left->key
            << "\nNewNode->right: " << node->key
            << "\n\n";

        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    if (balance < -1 && key < node->right->key) {
        cout << "Right Left Case"
            << "\nPivotNode: " << node->key
            << "\nPivotNode->right: "  << node->right->key
            << "\nPivotNode->right->left: " << node->right->left->key
            << "\n\n";

        cout << "result:" 
            << "\nNewNode: " << node->right->left->key
            << "\nNewNode->left: " << node->key
            << "\nNewNode->right: " << node->right->key
            << "\n\n";

        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node; 
}


int main() { 
    Node *root = nullptr; 

    int N;
    cin >> N;
    while(N--) {
        int tmp;
        cin >> tmp;
        root = insert(root, tmp); 
    }

    return 0; 
}