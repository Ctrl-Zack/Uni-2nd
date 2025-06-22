#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct data {
    int id;
    char nama[31];
    int warisan;
    _Bool status;
} Keluarga;

typedef struct node_t {
    Keluarga vl;
    struct node_t *_left, *_right;
} Node;

typedef struct btree_t {
    Node *_root;
    unsigned int _size;
} BTree;

void tree_init(BTree *tr);
Node *create_new_node(Keluarga value);
Node *tree_search(Node *root, int target);
void tree_insert(BTree *tr, Keluarga value);
Node *_tree_insert(Node *nd, Keluarga value);

void tree_init(BTree *tr) {
    tr->_root = NULL;
    tr->_size =0;
}

Node *create_new_node(Keluarga value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vl.id = value.id;
    strncpy(newNode->vl.nama, value.nama, 31);
    newNode->vl.warisan = value.warisan;
    newNode->vl.status = value.status;
    newNode->_left = newNode->_right = NULL;
    return newNode;
}

Node *tree_search(Node *root, int target) {
    if(root == NULL || root->vl.id == target) return root;
    if(root->vl.id > target) return tree_search(root->_left, target);
    return tree_search(root->_right, target);
}

void tree_insert(BTree *tr, Keluarga value) {
    if(tree_search(tr->_root, value.id) == NULL) {
        tr->_root = _tree_insert(tr->_root, value);
        tr->_size++;
    }
}

Node *_tree_insert(Node *nd, Keluarga value) {
    if(nd == NULL) return create_new_node(value);
    if(nd->vl.id > value.id) nd->_left = _tree_insert(nd->_left, value);
    if(nd->vl.id < value.id) nd->_right = _tree_insert(nd->_right, value);
    return nd;
}

void print_in_order(Node *root) {
    if(root == NULL) return;
    print_in_order(root->_left);
    if(root->vl.status == 1) printf("id: %d - nama: %s - warisan: %d\n", root->vl.id, root->vl.nama, root->vl.warisan);
    else printf("meninggal\n");
    print_in_order(root->_right);
}

void Tambah_anggota_baru(BTree *tr, int id, char nama[], int warisan) {
    Keluarga baru;
    baru.id = id;
    strncpy(baru.nama, nama, 31);
    baru.warisan = warisan;
    baru.status = 1;

    tree_insert(tr, baru);
}

void wariskan(Node *root, int harta) {
    if (!root) return;

    
    if (root->_left && root->_right) {
        int waris_kiri = harta * 0.6;
        int waris_kanan = harta * 0.4;

        if (root->_left->vl.status == 1) root->_left->vl.warisan += waris_kiri;
        else wariskan(root->_left, waris_kiri);
        
        if (root->_right->vl.status == 1) root->_right->vl.warisan += waris_kanan;
        else wariskan(root->_right, waris_kanan);

    } else if(root->_left) {
        if (root->_left->vl.status == 1) root->_left->vl.warisan += harta;
        else wariskan(root->_left, harta);

    } else if(root->_right) {
        if (root->_right->vl.status == 1) root->_right->vl.warisan += harta;
        else wariskan(root->_right, harta);

    }
}

void mati(BTree *tr, int id) {
    Node *tewas = tree_search(tr->_root, id);
    if(!tewas || tewas->vl.status == 0) return;

    tewas->vl.status = 0;
    wariskan(tewas, tewas->vl.warisan);
    tewas->vl.warisan = 0;
}


int main() {
    BTree bst;
    tree_init(&bst);
    
    char opt;
    int id;

    Tambah_anggota_baru(&bst, 25, "kakek", 50);
    Tambah_anggota_baru(&bst, 13, "anak1", 80);
    Tambah_anggota_baru(&bst, 27, "anak2", 10);
    Tambah_anggota_baru(&bst, 12, "a1-cucu1", 90);
    Tambah_anggota_baru(&bst, 26, "a2-cucu3", 30);
    Tambah_anggota_baru(&bst, 29, "a2-cucu4", 100);
    Tambah_anggota_baru(&bst, 28, "u4-cicit1", 40);
    Tambah_anggota_baru(&bst, 30, "u4-cicit2", 60);

    print_in_order(bst._root);
    printf("\n\n");
    
    printf("matikan cucu4\n");
    mati(&bst, 29);
    print_in_order(bst._root);
    
    printf("\n\n");

    printf("matikan anak2\n");
    mati(&bst, 27);
    print_in_order(bst._root);
    
    printf("\n\n");
    
    printf("matikan kakek\n");
    mati(&bst, 25);
    print_in_order(bst._root);

}