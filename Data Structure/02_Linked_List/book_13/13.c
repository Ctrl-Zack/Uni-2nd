/*
# Task
    The digits of an integer are held on a linked list in reverse order, one digit per node.
    Write a function that, given pointers to two integers, performs a digit-by-digit addition
    and returns a pointer to the digits of the sum stored in reverse order. Note: This idea can
    be used to add arbitrarily large integers.
#
*/

#include <stdio.h>
#include <stdlib.h>    

typedef struct {
    char letter;
    Node *next;
} Node;

void init(Node **p) {
    *p = NULL;
}

Node *allocate(char letter) {
    Node *p = (Node*) malloc(sizeof(Node));
    if(p != NULL) {
        p->next = NULL;
        p->letter = letter;
    }
    return p;
}

void add(Node **p, char letter) {
    *p = allocate(letter);
}

int main() {
    Node *head;
    init(&head);
    add(&head, 'a');
    return 0;
}