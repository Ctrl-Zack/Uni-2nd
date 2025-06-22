#include <bits/stdc++.h>
using namespace std;

struct node {
    int data;
    int value;
    node* left;
    node* right;

    node(int val, int val2) {
        data = val;
        value = val2;
        left = right = nullptr;
    }
};

node* insert(node* root, int val, int cost) {
    if (!root) {
        return new node(val,cost);
    }
    if (val < root->data){ 
        root->left = insert(root->left, val,cost);
    }
    else if (val > root->data){ 
        root->right = insert(root->right, val,cost);
    }
    return root;
}
node *findnode(node * root, int val){
    if (!root){
        return nullptr;
    }
    if (root->data == val){
        return root;
    }
    if (val<root->data){
        return findnode(root->left, val);
    }
    else{
    return findnode(root->right, val);
    }
}
int findcost(node * root){
    if (!root){
        return -1;
    }
    if (root->left == nullptr && root->right == nullptr){
        return 0;
    }
    int leftcost = findcost(root->left);
    int rightcost = findcost(root->right);

    int lefttotal = -1, righttotal = -1;
    if (root->left && leftcost != -1){
        lefttotal = root->left->value + leftcost;
    }
    if (root->right && rightcost != -1){
        righttotal = root->right->value + rightcost;
    }
    if (lefttotal == -1){
        return righttotal;
    }
    if (righttotal == -1){
        return lefttotal;
    }
    return min(lefttotal, righttotal);
}
int main() {
    node* root = nullptr;
    int uang;
    cin>>uang;
    int n,r,a,w;
    cin>>n>>r;
    root = insert(root, r, 0);
    for (int i = 0; i<n-1; i++){
        cin>>a>>w;
        insert(root, a, w);
    }
    int t;
    cin>>t;
    int z;
    while (t--){
        cin>>z;
        node * start = findnode(root, z);
        if (!start){
            cout<<"bruhh -_-"<<endl;
            continue;
        }
        int mincost = findcost(start);
        if (mincost != -1 && mincost<=uang){
            cout<<"yey, bisa refreshing :)"<<endl;
        }
        else{
            cout<<"bruhh -_-"<<endl;
        }
    }
}