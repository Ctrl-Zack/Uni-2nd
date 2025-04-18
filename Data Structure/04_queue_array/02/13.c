/*
#
    Write declarations and functions to implement a priority queue. each item in the queue has a job 
    number (integer) and a priority number. Implement, at least, the following functions: (i) initialize 
    an empty queue, (ii) add a job in its appropriate place in the queue, (iii) delete and dispose of the 
    job at the head of the queue, and (iv) given a job number, remove that job from the queue
#
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct job_t{
    int job_num, priority;
} Job;

typedef struct priorityQueue_t {
    Job *_job;
    unsigned _size, _capacity;
} PQueue;

void PQ_init(PQueue *p_queue, unsigned capacity); // (i) initialize an empty queue
void PQ_push(PQueue *p_queue, Job job); // (ii) add a job in its appropriate place in the queue
void PQ_pop(PQueue *p_queue); // (iii) delete and dispose of the job at the head of the queue
void PQ_deleteJob(PQueue *p_queue, int jobNumber); // (iv) given a job number, remove that job from the queue
_Bool PQ_isEmpty(PQueue *p_queue);
int PQ_front(PQueue *p_queue);

void PQ_init(PQueue *p_queue, unsigned capacity) {
    p_queue->_job = (Job*) malloc(sizeof(Job) * capacity);
    p_queue->_size = 0;
    p_queue->_capacity = capacity;
}

void PQ_push(PQueue *p_queue, Job job) {
    if(p_queue->_size == p_queue->_capacity)
        return;
    p_queue->_job[p_queue->_size].job_num = job.job_num;
    p_queue->_job[p_queue->_size].priority = job.priority;
    p_queue->_size++;
}

void PQ_pop(PQueue *p_queue) {
    if(PQ_isEmpty(p_queue)) return;
    int index = PQ_front(p_queue);
    for (int i = index; i < p_queue->_size; i++) {
        p_queue->_job[i] = p_queue->_job[i + 1];
    }
    p_queue->_size--;
}

void PQ_deleteJob(PQueue *p_queue, int jobNumber) {
    if(PQ_isEmpty(p_queue)) return;

    for (int i = 0; i < p_queue->_size; i++) {
        if(p_queue->_job[i].job_num == jobNumber) {
            for (int j = i; j < p_queue->_size; j++) {
                p_queue->_job[j] = p_queue->_job[j + 1];
            }
            p_queue->_size--;
            break;
        }
    }
}

_Bool PQ_isEmpty(PQueue *p_queue) {
    return (p_queue->_size == 0);
}

int PQ_front(PQueue *p_queue) {
    if(PQ_isEmpty(p_queue)) {
        puts("Queue is empty");
        return -1;
    }

    int maxPriority = INT_MIN;
    int idx = -1;

    for (int i = 0; i < p_queue->_size; i++) {
        if(maxPriority == p_queue->_job[i].priority && idx > -1 && p_queue->_job[idx].job_num < p_queue->_job[i].job_num) {
            maxPriority = p_queue->_job[i].priority;
            idx = i;
        } else if(maxPriority < p_queue->_job[i].priority) {
            maxPriority = p_queue->_job[i].priority;
            idx = i;
        }
    }
    
    return idx;
}

char prompt() {
    char choice;

    printf("\e[1;1H\e[2J");
    puts("=== Priority Queue ===");
    puts("1. Push a new job");
    puts("2. Pop a job");
    puts("3. delete a job");
    puts("4. View front element (by priority)");
    puts("5. Check if queue is empty");
    puts("0. Exit");
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    return choice;
}

int main() {
    PQueue pq;
    unsigned n;
    
    printf("array capacity: ");
    scanf(" %u", &n);

    PQ_init(&pq, n);

    char choice;

    do {
        choice = prompt();

        switch (choice) {
            case '1':
                if(pq._size < pq._capacity) {
                    Job jp;
                    puts("Enter job number and priority to push:");
                    scanf(" %d %d", &jp.job_num, &jp.priority);
                    PQ_push(&pq, jp);
                    puts("Job pushed.");
                } else {
                    puts("array capacity is full");
                }
                break;
            case '2':
                PQ_pop(&pq);
                puts("Job popped.");
                break;
            case '3':
                int jobNum;
                puts("Enter job number to delete:");
                scanf(" %d", &jobNum);
                PQ_deleteJob(&pq, jobNum);
                break;
            case '4':
                if(PQ_front(&pq) != -1) printf("front: %d\n", pq._job[PQ_front(&pq)].job_num);
                break;
            case '5':
                if (PQ_isEmpty(&pq))
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

    // Job arr[5] = {{10, 50}, {30, 30}, {20, 40}, {50, 20}, {40, 10}};

    // for (int i = 0; i < 5; i++) {
    //     PQ_push(&pq, arr[i]);
    // }
    
    // int index = PQ_front(&pq);
    // printf("%d\n", pq._job[index].job_num);
    // PQ_pop(&pq);
    // index = PQ_front(&pq);
    // printf("%d\n", pq._job[index].job_num);
    // PQ_pop(&pq);
    // index = PQ_front(&pq);
    // printf("%d\n", pq._job[index].job_num);
    // PQ_pop(&pq);
    // index = PQ_front(&pq);
    // printf("%d\n", pq._job[index].job_num);
    // PQ_pop(&pq);
    // index = PQ_front(&pq);
    // printf("%d\n", pq._job[index].job_num);
    // PQ_pop(&pq);

    return 0;
}