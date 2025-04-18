#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node_t {
    char value;
    struct node_t *next;
} Node;

typedef struct stack_t {
    unsigned _size;
    Node *_top;
} Stack;

void init(Stack *st);
_Bool isEmpty(Stack *st);
void push(Stack *st, char value);
void pop(Stack *st);

void init(Stack *st) {
    st->_size = 0;
    st->_top = NULL;
}

_Bool isEmpty(Stack *st) {
    return (st->_top == NULL);
}

void push(Stack *st, char value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    
    if(newNode) {
        newNode->value = value;
        st->_size++;

        if(isEmpty(st)) {
            newNode->next = NULL;
        } else {
            newNode->next = st->_top;
        }
        st->_top = newNode;
    }
}

void pop(Stack *st) {
    if(isEmpty(st)) {
        return;
    }
    Node *tmp = st->_top;
    st->_top = tmp->next;
    free(tmp);
    st->_size--;
}

void solve(int n) {
    Stack bracket;
    init(&bracket);

    int ans = 0;
    char str[n];
    scanf("%s", str);

    for (int i = 0; i < n; i++) {
        if(str[i] == '(') {
            push(&bracket, str[i]);
        } else if(str[i] == ')') {
            if(isEmpty(&bracket)) ans++;
            else pop(&bracket);
        }
    }
    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        scanf(" %d", &n);
        solve(n);
    }
}