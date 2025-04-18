#include <stdlib.h>
#include <stdio.h>

struct Node_St {
    int value;
    struct Node_St *next;
};
typedef struct Node_St Node_St;

struct Stack {
    unsigned _size;
    Node_St *_top;
};
typedef struct Stack Stack;


void stack_init(Stack *st);
int stack_top(Stack *st);
_Bool stack_isEmpty(Stack *st);
void stack_push(Stack *st, int value);
void stack_pop(Stack *st);


void stack_init(Stack *st) {
    st->_top = NULL;
    st->_size = 0;
}

int stack_top(Stack *st) {
    if(!stack_isEmpty(st))
        return st->_top->value;
    return -1;
}

_Bool stack_isEmpty(Stack *st) {
    return (st->_top == NULL);
}

void stack_push(Stack *st, int value) {
    Node_St *newNode = (Node_St *)malloc(sizeof(Node_St));
    
    if(newNode) {
        newNode->value = value;
        st->_size++;
        
        if(stack_isEmpty(st)) {
            newNode->next = NULL;
        } else {
            newNode->next = st->_top;
        }
        st->_top = newNode;
    }
}

void stack_pop(Stack *st) {
    if(!stack_isEmpty(st)) {
        Node_St *tmp = st->_top;
        st->_top = st->_top->next;
        free(tmp);
        st->_size--;
    }
}

void search(Stack *st, int value) {
    _Bool found = 0;
    Stack tmp;
    stack_init(&tmp);
    while(stack_isEmpty(st)) {
        if(st->_top->value != value) {
            stack_push(&tmp, st->_top->value);
            stack_pop(st);
        } else {
            printf("found : %d\n", value);
            found = 1;
            stack_pop(st);
            break;
        }
    }
    if(found) {
        while(stack_isEmpty(&tmp)) {
            stack_push(st, tmp._top->value);
            stack_pop(&tmp);
        }
    }
}

int main() {
    Stack st;
    stack_init(&st);
    stack_push(&st, 1);
    stack_push(&st, 2);
    stack_push(&st, 5);
    stack_push(&st, 6);
    stack_push(&st, 7);
    stack_push(&st, 16);
    stack_push(&st, 10);
    stack_push(&st, 6);
    stack_push(&st, 14);
    
    search(&st, 6);

    return 0;
}