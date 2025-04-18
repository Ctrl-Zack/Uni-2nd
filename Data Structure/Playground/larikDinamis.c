#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dArray_t {
    int *_arr;
    int _size, _capacity;
} Darray;

typedef struct larik_t {
    Darray **_arr;
    int _size, _capacity;
} Larik;

void L_init(Larik *L) {
    L->_arr = (Larik *)malloc(sizeof(Larik) * 2);
    L->_size = 0u;
    L->_capacity = 2u;
}

void D_init(Darray *D) {
    D->_arr = (Darray *)malloc(sizeof(Darray) * 2);
    D->_size = 0u;
    D->_capacity = 2u;
}

void dArray_pushBack(Darray *darray, int value) {
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
            newArr[it] = darray->_arr[it];
        
        int *oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size++] = value;
}

void L_pushBack(Larik *L, Darray *D) {
    if (L->_size + 1 > L->_capacity) {
        unsigned it;
        L->_capacity *= 2;
        Darray **newArr = (Darray **) malloc(sizeof(Darray *) * L->_capacity);

        for (it=0; it < L->_size; ++it)
            newArr[it] = L->_arr[it];
        
        int *oldL = L->_arr;
        L->_arr = newArr;
        free(oldL);
    }
    L->_arr[L->_size++] = D;
}

void getPrompt(Larik *L, char str[]) {
    if(strcmp(str, "add") == 0) {
        int L,X,Y;
        scanf(" %d %d %d", &L, &X, &Y);
        return;
    }
    
    if(strcmp(str, "new") == 0) {

        return;
    }
    
    if(strcmp(str, "out") == 0) {
        int L,Z;
        scanf(" %d %d", &L, &Z);
        return;
    }
}

int main() {
    Larik L;
    L_init(&L);

    int n;
    char prompt[4];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", prompt);
        getPrompt(&L, prompt);    
    }
    
    return 0;
}