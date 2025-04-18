/*
#
    Show how to implement a queue using two stacks.
#
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t {
    int *_element, _topIndex;
    unsigned int _size, _capacity;
} Stack;

void stack_init(Stack *stack, unsigned stackSize);
_Bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int  stack_top(Stack *stack);

void stack_init(Stack *stack, unsigned stackSize) {
    stack->_element  = (int*) malloc(sizeof(int) * stackSize);
    stack->_size     = 0;
    stack->_topIndex = -1;
    stack->_capacity = stackSize;
}

_Bool stack_isEmpty(Stack *stack) {
    return (stack->_topIndex == -1);
}

void stack_push(Stack *stack, int value) {
    if (stack->_size + 1 <= stack->_capacity) {
        stack->_element[++stack->_topIndex] = value;
        stack->_size++;
    }
}

void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        stack->_topIndex--;
        stack->_size--;
    }
}

int stack_top(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        return stack->_element[stack->_topIndex];
    }
    return 0;
}

/*############################################################################################*/

_Bool queue_isEmpty(Stack *stack_1, Stack *stack_2);
void queue_push(Stack *stack_1, int value);
void queue_pop(Stack *stack_1, Stack *stack_2);
void queue_front(Stack *stack_1, Stack *stack_2);

_Bool queue_isEmpty(Stack *stack_1, Stack *stack_2) {
    return stack_isEmpty(stack_1) && stack_isEmpty(stack_2);
}

void queue_push(Stack *stack_1, int value) {
    stack_push(stack_1, value);
}

void queue_pop(Stack *stack_1, Stack *stack_2) {
    if (stack_isEmpty(stack_2)) {
        while (!stack_isEmpty(stack_1)) {
            stack_push(stack_2, stack_top(stack_1));
            stack_pop(stack_1);
        }
    }
    if (!stack_isEmpty(stack_2)) {
        stack_pop(stack_2);
    }
}

void queue_front(Stack *stack_1, Stack *stack_2) {
    if(queue_isEmpty(stack_1, stack_2)) {
        puts("Queue is empty");
        return;
    }

    if (stack_isEmpty(stack_2)) {
        while (!stack_isEmpty(stack_1)) {
            stack_push(stack_2, stack_top(stack_1));
            stack_pop(stack_1);
        }
    }
    if (!stack_isEmpty(stack_2)) {
        printf("Front element: %d\n", stack_top(stack_2));
        return;
    }
}

/*############################################################################################*/

char prompt() {
    char choice;

    printf("\e[1;1H\e[2J");
    puts("=== Queue (2-Stack Implementation) ===");
    puts("1. Push an element");
    puts("2. Pop an element");
    puts("3. View front element");
    puts("4. Check if queue is empty");
    puts("0. Exit");
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    return choice;
}


int main() {
    Stack st1, st2;
    unsigned st_size;
    
    printf("array capacity: ");
    scanf(" %u", &st_size);

    stack_init(&st1, st_size);
    stack_init(&st2, st_size);
    
    char choice;

    do {
        choice = prompt();

        switch (choice) {
            case '1':
                if(st1._size < st1._capacity) {
                    int value;
                    puts("Enter value to push:");
                    scanf(" %d", &value);
                    queue_push(&st1, value);
                    puts("Value pushed.");
                } else {
                    puts("array capacity is full");
                }
                break;
            case '2':
                queue_pop(&st1, &st2);
                puts("Element popped.");
                break;
            case '3':
                queue_front(&st1, &st2);
                break;
            case '4':
                if (queue_isEmpty(&st1, &st2))
                    puts("Queue is empty.");
                else
                    puts("Queue is not empty.");
                break;
            case '0':
                puts("Exiting program.");
                break;
            default:
                puts("Invalid choice! Please try again.");
        }
        getch();
    } while (choice != '0');

    return 0;
}