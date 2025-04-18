/*
a stack, S1, contains some numbers in arbitrary order. using another stack, S2, for temporary 
storage, show how to sort the numbers in S1 such that the smallest is at the top of S1 and 
the largest is at the bottom.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct stackarr_t {
    int *_element, _topIndex;
    unsigned int _size, _capacity;
} StackArray;

void stackArray_init(StackArray *stack, unsigned stackSize);
_Bool stackArray_isEmpty(StackArray *stack);
void stackArray_push(StackArray *stack, int value);
void stackArray_pop(StackArray *stack);
int  stackArray_top(StackArray *stack);

void stackArray_init(StackArray *stack, unsigned stackSize) {
    stack->_element  = (int*) malloc(sizeof(int) * stackSize);
    stack->_size     = 0;
    stack->_topIndex = -1;
    stack->_capacity = stackSize;
}

_Bool stackArray_isEmpty(StackArray *stack) {
    return (stack->_topIndex == -1);
}

void stackArray_push(StackArray *stack, int value) {
    if (stack->_size + 1 <= stack->_capacity) {
        stack->_element[++stack->_topIndex] = value;
        stack->_size++;
    }
}

void stackArray_pop(StackArray *stack) {
    if (!stackArray_isEmpty(stack)) {
        stack->_topIndex--;
        stack->_size--;
    }
}

int stackArray_top(StackArray *stack) {
    if (!stackArray_isEmpty(stack)) {
        return stack->_element[stack->_topIndex];
    }
    return 0;
}

void sort_stack(StackArray *S1) {
    StackArray S2;
    stackArray_init(&S2, S1->_capacity);

    int idx=1;

    while (!stackArray_isEmpty(S1)) {
        int tmp = stackArray_top(S1);
        stackArray_pop(S1);

        while (!stackArray_isEmpty(&S2) && stackArray_top(&S2) > tmp) {
            stackArray_push(S1, stackArray_top(&S2));
            stackArray_pop(&S2);
        }

        stackArray_push(&S2, tmp);
        idx++;
    }

    while (!stackArray_isEmpty(&S2)) {
        stackArray_push(S1, stackArray_top(&S2));
        stackArray_pop(&S2);
    }
}

int main() {
    int num_of_element;
    puts("number of elements :");
    scanf("%d", &num_of_element);

    StackArray S1;
    stackArray_init(&S1, num_of_element);

    // stack_push(&S1, 1);
    // stack_push(&S1, 3);
    // stack_push(&S1, 9);
    // stack_push(&S1, 4);
    // stack_push(&S1, 7);
    // stack_push(&S1, 2);
    // stack_push(&S1, 6);
    // stack_push(&S1, 5);
    // stack_push(&S1, 8);
    
    for (int i = 0; i < num_of_element; i++) {
        int input_tmp;
        scanf("%d", &input_tmp);
        stackArray_push(&S1, input_tmp);
    }

    sort_stack(&S1);

    puts("sorted stack: ");
    while (!stackArray_isEmpty(&S1)) {
        printf("%d ", stackArray_top(&S1));
        stackArray_pop(&S1);
    }

    return 0;
}