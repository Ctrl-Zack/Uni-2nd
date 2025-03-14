#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  

struct Node {
    char value;
    struct Node *next;
};
typedef struct Node Node_t;


Node_t *create_new_node(char letter) {
    Node_t *p = (Node_t*) malloc(sizeof(Node_t));
    if(p != NULL) {
        p->value = letter;
        p->next = NULL;
    }
    return p;
}

void insert_behind(Node_t **head, char letter){
    Node_t *newNode = create_new_node(letter);

    if(*head == NULL) {
        *head = newNode;
        newNode->value = letter;
    } else {
        Node_t *tmp = *head;
    
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
}

void insert_front(Node_t **head, char letter) {
    Node_t *newNode = create_new_node(letter);
    newNode->next = *head;
    *head = newNode;
}

void printList(Node_t *head) {
    Node_t *tmp = head;
    while (tmp != NULL) {
        printf("%c - ", tmp->value);
        tmp = (Node_t *) tmp->next;
    }
    printf("\n");
}

int main() {
    char word1[256], word2[256];
    
    Node_t *head = NULL;
    Node_t *head2 = NULL;
    
    scanf("%s", word1);
    
    for (int i = 0; i < strlen(word1); i++) {
        insert_behind(&head, word1[i]);
        insert_front(&head2, word1[i]);
    }

    printList(head);
    printList(head2);

    return 0;
}