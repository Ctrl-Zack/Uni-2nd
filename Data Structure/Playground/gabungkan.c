#include<stdio.h>
#include<stdlib.h>

typedef struct node_t {
    int data;
    struct node_t *next;
} Node;

typedef struct list_t {
    Node *head;
    unsigned size;
} Llist;

void init(Llist *list) {
    list->head = NULL;
    list->size = 0;
}

void pushBack(Llist *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    list->size++;
    
    Node *tmp = list->head;
    if(list->head == NULL) list->head = newNode;
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = newNode;
    }
}

void popFront(Llist *list) {
    if(list->head != NULL) {
        list->size--;
        Node *tmp = list->head;
        list->head = tmp->next;
        free(tmp);
    }
}

void gabung(Llist *list1, Llist *list2) {
    int len = 1;
    Node *gabungAwal = list1->head;
    Node *gabungAkhir = list2->head;
    
    while(len < list1->size / 2) {
        gabungAwal = gabungAwal->next;
        len++;
    }

    if(list1->size % 2 != 0) gabungAwal = gabungAwal->next;

    while(gabungAkhir->next != NULL) gabungAkhir = gabungAkhir->next;
    gabungAkhir->next = gabungAwal->next;
    gabungAwal->next = list2->head;
}

int main() {
    Llist list1, list2;
    init(&list1);
    init(&list2);

    int a,b,buff;
    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        scanf("%d", &buff);
        pushBack(&list1, buff);
    }
    
    scanf("%d", &b);
    for (int i = 0; i < b; i++) {
        scanf("%d", &buff);
        pushBack(&list2, buff);
    }

    gabung(&list1, &list2);

    while(list1.head != NULL) {
        printf("%d", list1.head->data);
        popFront(&list1);
    }
    printf("\n");
    return 0;
}