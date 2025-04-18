/*
Show the contents of post for the expression (2 + 3) * (8 / 4) - 6
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stackarr_t {
    int *_element, _topIndex;
    unsigned int _size, _capacity;
} StackArray;

void stackArray_init(StackArray *stack, unsigned stackSize);
_Bool stackArray_isEmpty(StackArray *stack);
void stackArray_push(StackArray *stack, int value);
void stackArray_pop(StackArray *stack);
int  stackArray_top(StackArray *stack);

void stackArray_init(StackArray *stack, unsigned int stackSize) {
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

int get_precedence(char opt) {
    switch (opt) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}

_Bool is_operand(char opd) {
    return (opd >= '0' && opd <= '9');
}

void convert_infix_to_postfix(char infix[]) {
    
    int strl = strlen(infix);
    char postfix[strl];
    int idx = 0;

    StackArray operators;
    stackArray_init(&operators, strl);

    for(int index = 0; index < strl; index++) {
        if(is_operand(infix[index])) {
            postfix[idx] = infix[index];
            idx++;
        } else if(infix[index] == '(') {
            stackArray_push(&operators, '(');
        } else if(infix[index] == ')') {
            while(stackArray_top(&operators) != '(') {
                postfix[idx] = stackArray_top(&operators);
                idx++;
                stackArray_pop(&operators);
            }
            stackArray_pop(&operators);
        } else {
            while(!stackArray_isEmpty(&operators) && stackArray_top(&operators) != '(' && get_precedence(stackArray_top(&operators)) >= get_precedence(infix[index])) {
                postfix[idx] = stackArray_top(&operators);
                idx++;
                stackArray_pop(&operators);
            }
            stackArray_push(&operators, infix[index]);
        }
    }
    
    while(!stackArray_isEmpty(&operators)) {
        postfix[idx] = stackArray_top(&operators);
        stackArray_pop(&operators);
    }
    postfix[++idx] = '\0';
    printf("postfix notation: %s\n", postfix);
}

int main() {
    // char infix_notation[] = "a*b*(n-c)+(d*(n-e))";
    char infix_notation[] = "(2+3)*(8/4)-6";
    printf("infix notation: %s\n", infix_notation);
    convert_infix_to_postfix(infix_notation);

    return 0;
}