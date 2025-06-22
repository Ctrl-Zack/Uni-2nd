#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value;
    struct node *next;
} Node_St;

typedef struct stack {
    unsigned _size;
    Node_St *_top;
} Stack;

typedef struct mp {
    int x, y;
} Map;


Map robotMap = {0, 0};


void stack_init(Stack *st) {
    st->_top = NULL;
    st->_size = 0;
}

_Bool stack_isEmpty(Stack *st) {
    return (st->_top == NULL);
}

int stack_top(Stack *st) {
    if(!stack_isEmpty(st))
        return st->_top->value;
    return -1;
}

void stack_push(Stack *st, char value) {
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

int main() {
    char input[128];
    Stack undo;
    stack_init(&undo);

    scanf("%s", input);

    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if(input[i] == 'B' && !stack_isEmpty(&undo)) {
            char tmp = stack_top(&undo);
            if(tmp == 'U') { robotMap.y--; }
            else if(tmp == 'D') { robotMap.y++; }
            else if(tmp == 'L') { robotMap.x++; }
            else if(tmp == 'R') { robotMap.x--; }
            stack_pop(&undo);
        } else {
            stack_push(&undo, input[i]);
        }
        if(input[i] == 'U') { robotMap.y++; }
        else if(input[i] == 'D') { robotMap.y--; }
        else if(input[i] == 'L') { robotMap.x--; }
        else if(input[i] == 'R') { robotMap.x++; }

        // printf("%d === %d, %d\n", i, robotMap.x, robotMap.y);
    }

    printf("Posisi akhir robot: (%d, %d)", robotMap.x, robotMap.y);
    
}