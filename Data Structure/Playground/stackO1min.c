#include<stdio.h>
#include<stdlib.h>

typedef struct node_t {
    int value;
    struct node_t *next;
} Node;

typedef struct stack_t {
    Node *st;
    Node *minSt;
    unsigned size;
} Stack;

void init(Stack *st) {
    st->st = NULL;
    st->minSt = NULL;
    st->size = 0;
}

_Bool isEmpty(Stack *st) {
    return (st->st == NULL);
}

void push(Stack *st, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    
}

void pop(Stack *st) {

}

int main() {

}