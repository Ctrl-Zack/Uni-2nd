#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int height;
    int index;
} Pair;

typedef struct stackNode_t {
    Pair data;
    struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;


void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, Pair value);
void stack_pop(Stack *stack);
Pair stack_top(Stack *stack);

void stack_init(Stack *stack) {
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, Pair value) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        newNode->next = stack->_top;
        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

Pair stack_top(Stack *stack) {
    Pair dummy = {-1, -1};
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return dummy;
}


int main() {
    int n;
    scanf("%d", &n);
    
    int H[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &H[i]);
    }

    Stack st;
    stack_init(&st);

    long long total = 0;

    for (int i = 0; i < n; i++) {
        while (!stack_isEmpty(&st) && stack_top(&st).height <= H[i]) {
            stack_pop(&st);
        }

        int Ai = 0;
        if (stack_isEmpty(&st)) {
            Ai = i + 1;
        } else {
            Ai = i - stack_top(&st).index;
        }

        Pair now = {H[i], i};
        stack_push(&st, now);

        total += Ai;
    }

    printf("%lld\n", total);
    return 0;
}