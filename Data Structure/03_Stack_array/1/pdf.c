/*
Tambahkanlah function untuk mencari suatu elemen dalam stack
Tambahkanfunction untuk mengedit suatu elemen dalam stack
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

int stackArray_search(StackArray *stack, int value) {
    for (int i = 0; i <= stack->_topIndex; i++) {
        if (stack->_element[i] == value) {
            return i;
        }
    }
    return -1;
}

void stackArray_edit(StackArray *stack, int index, int newValue) {
    if (index >= 0 && index <= stack->_topIndex) {
        stack->_element[index] = newValue;
    }
}

void stackArray_print(StackArray *stack) {
    StackArray tmp;
    stackArray_init(&tmp, stack->_capacity);

    while (!stackArray_isEmpty(stack)) {
        printf("%d ", stackArray_top(stack));
        stackArray_push(&tmp, stackArray_top(stack));
        stackArray_pop(stack);
    }
    
    while(!stackArray_isEmpty(&tmp)) {
        stackArray_push(stack, stackArray_top(&tmp));
        stackArray_pop(&tmp);
    }
}

int main(int argc, char const *argv[]) {
    StackArray myStack;
    int capacity, choice, value, index, newValue;
    
    puts("Enter the capacity of the stack :");
    scanf("%d", &capacity);
    
    stackArray_init(&myStack, capacity);
    
    while(1) {
        printf("\nStack Operations Menu:\n");
        puts("1. Push an element");
        puts("2. Pop an element");
        puts("3. Print stack");
        puts("4. Search for an element");
        puts("5. Edit an element");
        puts("6. Exit");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(myStack._size >= capacity) {
                    puts("Maximum stack capacity reached.");
                } else {
                    puts("Enter value to push: ");
                    scanf("%d", &value);
                    stackArray_push(&myStack, value);
                    printf("%d", myStack._size);
                    puts("Element pushed to stack.");
                }
                break;
            
            case 2:
                if (!stackArray_isEmpty(&myStack)) {
                    stackArray_pop(&myStack);
                    puts("Element popped from stack.");
                } else {
                    puts("Stack is empty.");
                }
                break;
            
            case 3:
                puts("Current stack: ");
                stackArray_print(&myStack);
                printf("\n");
                break;
            
            case 4:
                puts("Enter value to search: ");
                scanf("%d", &value);
                index = stackArray_search(&myStack, value);
                if (index != -1) {
                    printf("Element %d found at index %d.\n", value, index);
                } else {
                    printf("Element not found in the stack.\n");
                }
                break;
            
            case 5:
                printf("Enter index to edit: ");
                scanf("%d", &index);
                if(index >= capacity) {
                    puts("invalid index.");
                } else {
                    printf("Enter new value: ");
                    scanf("%d", &newValue);
                    stackArray_edit(&myStack, index, newValue);
                    printf("Element at index %d edited to %d.\n", index, newValue);
                }
                break;
            
            case 6:
                puts("Exiting program.");
                free(myStack._element);
                return 0;

            default:
                puts("Invalid choice. Please try again.");
        }
    }

    return 0;
}