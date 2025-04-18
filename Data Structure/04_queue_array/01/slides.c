/*
# Task
    - Tambahkanlah function untuk mencari suatu elemen dalam queue
    - Tambahkan function untuk mengedit suatu elemen dalam queue 
    - Carilah nilai total, rata-rata, terbesar dan terkecil dari elemen-elemen queue dalam function tersendiri
    * gunakan circular array
#
*/

#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

typedef struct queuearr_t {
    int *_element;
    int _front, 
        _rear;
    unsigned _size, _capacity;
} QueueArray;

void qArr_init(QueueArray *queue, unsigned queueSize);
_Bool qArr_isEmpty(QueueArray *queue);
void qArr_push(QueueArray *queue, int value);
void qArr_pop(QueueArray *queue);
int  qArr_front(QueueArray *queue);
int qArr_search(QueueArray *queue, int target);
void qArr_edit(QueueArray *queue, int index, int newVal);
int qArr_total_elements(QueueArray *queue);
float qArr_avg_elements(QueueArray *queue);
int qArr_min_elements(QueueArray *queue);
int qArr_max_elements(QueueArray *queue);

void qArr_init(QueueArray *queue, unsigned queueSize) {
    queue->_element = (int*) malloc(sizeof(int) * queueSize);
    queue->_front = -1;
    queue->_rear  = -1;
    queue->_size  = 0;
    queue->_capacity = queueSize;
}

_Bool qArr_isEmpty(QueueArray *queue) {
    return (queue->_front == -1);
}

void qArr_push(QueueArray *queue, int value) {
    if (queue->_size == queue->_capacity)
        return;
    if (queue->_front == -1) {
        queue->_front = 0;
    }
    queue->_rear = (queue->_rear + 1) % queue->_capacity;
    queue->_element[queue->_rear] = value;
    queue->_size++; 
}

void qArr_pop(QueueArray *queue) {
    if (queue->_size == 0)
       return;
    if (queue->_front == queue->_rear)
        queue->_front = queue->_rear = -1;
    else
        queue->_front = (queue->_front + 1) % queue->_capacity;
    queue->_size--;
}

int qArr_front(QueueArray *queue) {
    if (queue->_size == 0)
        return -1;
    return queue->_element[queue->_front];
}

int qArr_search(QueueArray *queue, int target) {
    for (int i = 0; i < queue->_size; i++) {
        if(queue->_element[i] == target)
            return i;
    }
    return -1;
}

void qArr_edit(QueueArray *queue, int index, int newVal) {
    if(index > queue->_size) return;
    queue->_element[index] = newVal;
}

int qArr_total_elements(QueueArray *queue) {
    int total = 0;
    for (int i = 0; i < queue->_size; i++) {
        total += queue->_element[i];
    }
    return total;
}

float qArr_avg_elements(QueueArray *queue) {
    int total = qArr_total_elements(queue);
    return total == 0 ? 0:((float)total / (float)queue->_size);
}

int qArr_min_elements(QueueArray *queue) {
    int min = INT_MAX;
    for (int i = 0; i < queue->_size; i++) {
        if(queue->_element[i] < min)
            min = queue->_element[i];
    }
    return min;
}

int qArr_max_elements(QueueArray *queue) {
    int max = INT_MIN;
    for (int i = 0; i < queue->_size; i++) {
        if(queue->_element[i] > max)
            max = queue->_element[i];
    }
    return max;
}

char queue_prompt() {
    char choice;

    printf("\e[1;1H\e[2J");
    puts("=== functions ===");
    puts("1. Push an element");
    puts("2. Pop an element");
    puts("3. View front element");
    puts("4. Search for a value");
    puts("5. Edit a value at index");
    puts("6. Get total of all elements");
    puts("7. Get average of elements");
    puts("8. Find minimum value");
    puts("9. Find maximum value");
    puts("0. Exit");
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    return choice;
}

int main(int argc, char const *argv[]) {
    QueueArray myQueue;
    qArr_init(&myQueue, SIZE);

    char choice;

    do {
        choice = queue_prompt();

        switch (choice) {
            case '1':
                if(myQueue._size < myQueue._capacity) {
                    int value;
                    puts("Enter value to push:");
                    scanf(" %d", &value);
                    qArr_push(&myQueue, value);
                    puts("Value pushed.");
                } else {
                    puts("array capacity is full");
                }
                break;
            case '2':
                qArr_pop(&myQueue);
                puts("Front element popped.");
                break;
            case '3':
                int front = qArr_front(&myQueue);
                if (front != -1)
                    printf("Front element: %d\n", front);
                else
                    puts("Queue is empty.");
                break;
            case '4':
                int target;
                puts("Enter value to search:");
                scanf(" %d", &target);
                int found = qArr_search(&myQueue, target);
                if (found != -1)
                    printf("Value %d found at index: %d.\n", target, found);
                else
                    puts("Value not found.");    
                break;
            case '5':
                int index, newVal;
                puts("Enter index to edit:");
                scanf(" %d", &index);
                puts("Enter new value:");
                scanf(" %d", &newVal);
                qArr_edit(&myQueue, index, newVal);
                puts("Value updated.");
                break;
            case '6':
                printf("Total of elements: %d\n", qArr_total_elements(&myQueue));
                break;
            case '7':
                printf("Average of elements: %.2f\n", qArr_avg_elements(&myQueue));
                break;
            case '8':
                printf("Minimum value: %d\n", qArr_min_elements(&myQueue));
                break;
            case '9':
                printf("Maximum value: %d\n", qArr_max_elements(&myQueue));
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