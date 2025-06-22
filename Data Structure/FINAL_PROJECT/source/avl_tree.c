#include "avl_tree.h"

int8_t compareNumeric(const char *a, const char *b)
{
    while (*a == '0') a++;
    while (*b == '0') b++;

    uint8_t lenA = 0, lenB = 0;
    const char *pa = a, *pb = b;
    while (*pa++) lenA++;
    while (*pb++) lenB++;

    if (lenA != lenB) return (lenA > lenB) ? 1 : -1;

    while (*a && *b)
    {
        if (*a != *b) return (*a > *b) ? 1 : -1;
        a++; b++;
    }
    return 0;
}

void getMaxNumber(AVLNode *root, char *max_nomor)
{
    while (root && root->right != NULL) root = root->right;
    if (root) strcpy(max_nomor, root->data.nomor);
}

void generateNextNumber(AVL *avl, char *buffer)
{
    if (avl->_root == NULL)
    {
        strcpy(buffer, "000001");
        return;
    }

    char max_nomor[MAX_NOKOMPONEN + 1] = "000000";
    getMaxNumber(avl->_root, max_nomor);

    const char *num_ptr = max_nomor;
    while (*num_ptr == '0') num_ptr++;

    uint32_t next_nomor = atoi(num_ptr);
    next_nomor += 1;

    sprintf(buffer, "%06d", next_nomor);
}


AVLNode* _avl_createNode(DataKomponen data)
{
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));

    if (!newNode) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->data.nomor, data.nomor, sizeof(newNode->data.nomor));
    newNode->data.nomor[sizeof(newNode->data.nomor) - 1] = '\0';
    strncpy(newNode->data.nama, data.nama, sizeof(newNode->data.nama));
    newNode->data.nama[sizeof(newNode->data.nama) - 1] = '\0';
    newNode->data.stock = data.stock;
    newNode->data.harga = data.harga;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;

    return newNode;
}

AVLNode* _search(AVLNode *root, const char *nomor_komponen)
{
    while (root != NULL)
    {
        int8_t compare = compareNumeric(nomor_komponen, root->data.nomor); 
        if (compare < 0) root = root->left;
        else if (compare > 0) root = root->right;
        else return root;
    }
    return NULL;
}

uint16_t _getHeight(AVLNode* node)
{
    if(node == NULL) return 0;
    return node->height;
}

uint16_t _max(uint16_t a, uint16_t b)
{
    return (a > b) ? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode)
{
    AVLNode* newParent = pivotNode->left;
    pivotNode->left = newParent->right;
    newParent->right = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParent->height = _max(_getHeight(newParent->left), _getHeight(newParent->right)) + 1;
    
    return newParent;
}

AVLNode* _leftRotate(AVLNode* pivotNode)
{
    AVLNode* newParent = pivotNode->right;
    pivotNode->right = newParent->left;
    newParent->left = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParent->height = _max(_getHeight(newParent->left), _getHeight(newParent->right)) + 1;
    
    return newParent;
}

AVLNode* _leftCaseRotate(AVLNode* node)
{
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node)
{
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node)
{
    node->left = _leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node)
{
    node->right = _rightRotate(node->right);
    return _leftRotate(node);
}

int16_t _getBalanceFactor(AVLNode* node)
{
    if(node == NULL) return 0;
    return (int16_t)(_getHeight(node->left) - _getHeight(node->right));
}

AVLNode* _insert_AVL(AVL *avl, AVLNode* node, DataKomponen data)
{
    if(node == NULL) return _avl_createNode(data);
    
    int8_t compare = compareNumeric(data.nomor, node->data.nomor);
    
    if(compare < 0) node->left = _insert_AVL(avl, node->left, data);
    else if(compare > 0) node->right = _insert_AVL(avl, node->right, data);
    
    node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1;
    
    int16_t balanceFactor = _getBalanceFactor(node);
    
    if (balanceFactor > 1)
    {
        if (node->left && compareNumeric(data.nomor, node->left->data.nomor) < 0) return _leftCaseRotate(node);
        else if (node->left) return _leftRightCaseRotate(node);
    }

    if (balanceFactor < -1)
    {
        if (node->right && compareNumeric(data.nomor, node->right->data.nomor) > 0) return _rightCaseRotate(node);
        else if (node->right) return _rightLeftCaseRotate(node);
    }

    return node;
}

AVLNode* _findMinNode(AVLNode *node)
{
    AVLNode *currNode = node;
    
    while (currNode && currNode->left != NULL) currNode = currNode->left;
    
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node, const char *nomor_komponen)
{
    if(node == NULL) return node;
    
    int8_t compare = compareNumeric(nomor_komponen, node->data.nomor);
    
    if(compare > 0) node->right = _remove_AVL(node->right, nomor_komponen);
    else if(compare < 0) node->left = _remove_AVL(node->left, nomor_komponen);
    else
    {
        AVLNode *temp;
        
        if((node->left == NULL) || (node->right == NULL))
        {
            temp = NULL;

            if(node->left == NULL) temp = node->right;  
            else if(node->right == NULL) temp = node->left;
            
            if(temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else *node = *temp;   
            
            free(temp);
        }
        else
        {
            temp = _findMinNode(node->right);
            strncpy(node->data.nomor, temp->data.nomor, sizeof(node->data.nomor));
            node->data.nomor[sizeof(node->data.nomor) - 1] = '\0';
            strncpy(node->data.nama, temp->data.nama, sizeof(node->data.nama));
            node->data.nama[sizeof(node->data.nama) - 1] = '\0';
            node->data.harga = temp->data.harga;
            node->data.stock = temp->data.stock;
            node->right = _remove_AVL(node->right, temp->data.nomor);
        }    
    }

	if(node == NULL) return node;
    
    node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1;

    int16_t balanceFactor = _getBalanceFactor(node);
    
    if(balanceFactor > 1 && _getBalanceFactor(node->left) >= 0) return _leftCaseRotate(node);
    if(balanceFactor > 1 && _getBalanceFactor(node->left) < 0) return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && _getBalanceFactor(node->right) <= 0) return _rightCaseRotate(node);
    if(balanceFactor < -1 && _getBalanceFactor(node->right) > 0) return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl)
{
    avl->_root = NULL;
    avl->_size = 0u;
}

_Bool avl_isEmpty(AVL *avl)
{
    return avl->_root == NULL;
}

_Bool avl_find(AVL *avl, const char *nomor_komponen)
{
    AVLNode *temp = _search(avl->_root, nomor_komponen);
    
    return temp != NULL;
}

void avl_insert(AVL *avl, DataKomponen data)
{
    if(!avl_find(avl, data.nomor))
    {
        avl->_root = _insert_AVL(avl, avl->_root, data);
        avl->_size++;
    }
}

void avl_remove(AVL *avl, const char *nomor_komponen)
{
    if(avl_find(avl, nomor_komponen))
    {
        avl->_root = _remove_AVL(avl->_root, nomor_komponen);
        avl->_size--;
    }
}

void indexedInorder(AVLNode *root)
{
    if (root)
    {
        indexedInorder(root->left);
        printf("|%10s |", root->data.nomor);
        printf("%30s |", root->data.nama);
        printf("%20f |", root->data.harga);
        printf("%20d |\n", root->data.stock);
        printf("+-----------+-------------------------------+---------------------+---------------------+\n");
        indexedInorder(root->right);
    }
}

void noIndexInorder(AVLNode *root)
{
    if (root)
    {
        noIndexInorder(root->left);
        printf("|%30s |", root->data.nama);
        printf("%20f |", root->data.harga);
        printf("%20d |\n", root->data.stock);
        printf("+-------------------------------+---------------------+---------------------+\n");
        noIndexInorder(root->right);
    }
}

void avl_free(AVLNode *root)
{
    if (root)
    {
        avl_free(root->left);
        avl_free(root->right);
        free(root);
    }
}