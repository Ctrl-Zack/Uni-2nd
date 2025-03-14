/*
# Task
    The children's game of "count-out” is played as follows: n children (numbered 1 to n) are arranged
    in a circle. A sentence consisting of m words is used to eliminate one child at a time until one
    child is left. Starting at child 1, the children are counted from 1 to m, and the mth child is eliminated.
    Starting with the child after the one just eliminated, the children are again counted from 1 to m,
    and the mth child eliminated. This is repeated until one child is left. Counting is done circularly,
    and eliminated children are not Counted. Write a program to read values for n and m and print the number
    of the last remaining child. Use a linked list to hold the children.
    Hint: Let the last node point to the first, creating a circular list.
#
*/

#include <stdio.h>
#include <stdlib.h>    
#include <string.h>

struct Node_t {
    int child;
    struct Node_t *next;
};
typedef struct Node_t Node_t;

void add_node_back(Node_t **head, int n) {
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    newNode->child = n;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node_t *tmp = *head;
        while(tmp->next != *head) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
        newNode->next = *head;
    }
}

void display_list(Node_t *head) {
    if(head == NULL) {
        printf("list is empty");
    }
    
    Node_t *tmp = head;
    
    do {
        printf("%d - ", tmp->child);
        tmp = tmp->next;
    } while(tmp != head);

    printf("\n");
}

int count_out(Node_t **head, int m) {
    Node_t *tmp = *head;
    Node_t *prev = NULL;

    while (tmp->next != *head || prev->next != *head) {
       int mTmp = m; 
        while(mTmp--) {
            prev = tmp;
            tmp = tmp->next;
        }
        if(tmp == *head) {    
            while (tmp->next != *head) {
                tmp = tmp->next;
            }

            tmp->next = (*head)->next;
            tmp = *head;
            *head = (*head)->next;

            printf("%d eliminated -- ", tmp->child);
            free(tmp);
            tmp = tmp->next;
        } else {
            prev->next = tmp->next;
            printf("%d eliminated -- ", tmp->child);
            free(tmp);
            tmp = tmp->next;
        }
    }

    printf("\n");
    return tmp->child;
}

void run(int n, int m) {
    // edge cases
    if(n == 1) {
        printf("Need more player (>= 2)");
        return;
    }
    
    if(m == 0) {
        printf("Winner : %d\n", n);
        return;
    }

    Node_t *head = NULL;

    for (int i = 1; i <= n; i++) {
        add_node_back(&head, i);
    }
    
    display_list(head);
    printf("Winner : %d\n", count_out(&head, m));
}

int main() {
    int nChildren;
    char mWord[256];

    scanf(" %d", &nChildren);
    scanf(" %s", mWord);
   
    int m = strlen(mWord) - 1;
    
    run(nChildren, m);

    return 0;
}