#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct queueNode_t {
    int data;
    struct queueNode_t *next;
} QueueNode;

typedef struct queue_t {
    QueueNode   *_front, 
                *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, int value);
void queue_pop(Queue *queue);
int queue_front(Queue *queue);
int  queue_size(Queue *queue);

void queue_init(Queue *queue) {
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, int value) {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pop(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

int queue_front(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        return (queue->_front->data);
    }
    return (int)0;
}

int queue_size(Queue *queue) {
    return queue->_size;
}


int main(int argc, char const *argv[]) {
    Queue myQueue;
    queue_init(&myQueue);

    int X,Y,Z;
    scanf("%d %d %d", &X, &Y, &Z);

    for (int i = 0; i < X; i++) {
        int a;
        scanf(" %d", &a);
        queue_push(&myQueue, a);
    }

    int index = 1;
    int ans = 0;
    int dapat = 0;
    _Bool freeBurger = 0;
    
    while(Y > 0 && !queue_isEmpty(&myQueue)) {
        int tmp = queue_front(&myQueue);
        if(index % Z == 0) {
            queue_pop(&myQueue);
            queue_push(&myQueue, tmp);
            ans++;
        } else {
            if(Y >= tmp) {
                Y -= tmp;
                queue_pop(&myQueue);
                if(dapat == X-1) freeBurger = 1;
            }
            dapat++;
        }
        
        index++;
    }

    printf("%d", ans);
    if(freeBurger) printf(" Yes Dapat burger gratis!!!");
    else printf(" NOO tidak Dapat :(");

    return 0;
}