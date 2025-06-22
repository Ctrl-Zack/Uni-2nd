#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define true                1
#define false               0
#define MAX_NOKOMPONEN      6
#define MAX_NAMAKOMPONEN    25
#define MAX_KOMPONEN        100000

typedef struct data_komponen_t {
    char nomor[MAX_NOKOMPONEN + 1];
    char nama[MAX_NAMAKOMPONEN + 1];
    int32_t stock;
    double harga;
} DataKomponen;

typedef struct AVLNode_t {
    DataKomponen data;
    struct AVLNode_t *left,*right;
    uint32_t height;
}AVLNode;

typedef struct AVL_t {
    AVLNode *_root;
    uint32_t _size;
} AVL;

int8_t compareNumeric(const char *a, const char *b);
void getMaxNumber(AVLNode *root, char *max_nomor);
void generateNextNumber(AVL *avl, char *buffer);
AVLNode* _avl_createNode(DataKomponen data);
AVLNode* _search(AVLNode *root, const char *nomor_komponen);
uint16_t _getHeight(AVLNode* node);
uint16_t _max(uint16_t a, uint16_t b);
AVLNode* _rightRotate(AVLNode* pivotNode);
AVLNode* _leftRotate(AVLNode* pivotNode);
AVLNode* _leftCaseRotate(AVLNode* node);
AVLNode* _rightCaseRotate(AVLNode* node);
AVLNode* _leftRightCaseRotate(AVLNode* node);
AVLNode* _rightLeftCaseRotate(AVLNode* node);
int16_t  _getBalanceFactor(AVLNode* node);
AVLNode* _insert_AVL(AVL *avl, AVLNode* node, DataKomponen data);
AVLNode* _findMinNode(AVLNode *node);
AVLNode* _remove_AVL(AVLNode* node, const char *nomor_komponen);
void avl_init(AVL *avl);
_Bool avl_isEmpty(AVL *avl);
_Bool avl_find(AVL *avl, const char *nomor_komponen);
void avl_insert(AVL *avl, DataKomponen data);
void avl_remove(AVL *avl, const char *nomor_komponen);
void indexedInorder(AVLNode *root);
void noIndexInorder(AVLNode *root);
void avl_free(AVLNode *root);


#endif