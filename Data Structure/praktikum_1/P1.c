#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node_t {
    char ch;
    struct node_t *next;
} Node;

typedef struct Stack {
    Node *_head;
    int _size;
} Stack;

void init(Stack *st) {
    st->_head = NULL;
    st->_size = 0;
}

_Bool isEmpty(Stack *st) {
    return (st->_head == NULL);
}

void push(Stack *st, char ch) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ch = ch;
    if(isEmpty(st)) {
        newNode->next = NULL;
    } else {
        newNode->next = st->_head;
    }
    st->_head = newNode;
    st->_size++;
}

void pop(Stack *st) {
    if(!isEmpty(st)) {
        Node *tmp = st->_head;
        st->_head = st->_head->next;
        free(tmp);
        st->_size--;
    }
}

void print(Stack *st) {
    while(!isEmpty(st)) {
        printf("%c", st->_head->ch);
        pop(st);
    }
}

int main() {
    Stack st;
    init(&st);

    char str[105];
    scanf("%s", str);
    for (int i = 0; i < strlen(str); i++) {
        if(str[i] == 'a' || str[i] == 'i' || str[i] == 'u' || str[i] == 'e' || str[i] == 'o' || str[i] == 'A' || str[i] == 'I' || str[i] == 'U' || str[i] == 'E' || str[i] == 'O') {
            push(&st, str[i]);
            push(&st, str[i]);
        } else {
            push(&st, str[i]);
        }
    }
    print(&st);
    
    return 0;    
}