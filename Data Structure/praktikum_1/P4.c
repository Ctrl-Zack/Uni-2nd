#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct pqueueNode_t {
    int data;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;


void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int value);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);


void pqueue_init(PriorityQueue *pqueue) {
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value) {
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (value > pqueue->_top->data) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                temp->next->data > value)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}


int getVal(char str[]) {
    int len = strlen(str);
    int idx = 0;
    int ans = 0;
    while(idx < len) {
        ans *= 10;
        switch (str[idx]) {
        case '!':
            ans += 1;
            break;
        case '@':
            ans += 2;
            break;
        case '#':
            ans += 3;
            break;
        case '$':
            ans += 4;
            break;
        case '%':
            ans += 5;
            break;
        case '^':
            ans += 6;
            break;
        case '&':
            ans += 7;
            break;
        case '*':
            ans += 8;
            break;
        case '(':
            ans += 9;
            break;
        default:
            break;
        }                
        idx++;
    }
    return ans;
}

int main(int argc, char const *argv[]) {
    PriorityQueue myPque;
    pqueue_init(&myPque);

    // printf("%d", getVal("#@@"));
    
    int n, M;
    char str[10];

    scanf("%d %d", &n, &M);
    
    while(n--) {
        scanf(" %s", str);
        
        int value = getVal(str);
        if(value <= M) pqueue_push(&myPque, value);

        if(!pqueue_isEmpty(&myPque) && pqueue_top(&myPque) == M) {
            while (!pqueue_isEmpty(&myPque) && pqueue_top(&myPque) == M) {
                printf("%d ", pqueue_top(&myPque));
                pqueue_pop(&myPque);
                M--;
            }
            printf("\n");
        } else {
            printf("\n");
        }
    }

    return 0;
}