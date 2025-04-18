#include <stdio.h>
#include <stdlib.h>

// Definisi node untuk singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Definisi list
typedef struct List {
    Node *head;
} List;

// Inisialisasi list
void list_init(List *list) {
    list->head = NULL;
}

// Menambahkan elemen ke akhir list
void list_append(List *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

// Fungsi forEachElement
void forEachElement(List *list, void (*func)(int *)) {
    Node *current = list->head;
    while (current != NULL) {
        func(&(current->data));
        current = current->next;
    }
}

// Fungsi cetak elemen
void printElement(int *elem) {
    printf("%d ", *elem);
}

// Fungsi mengalikan elemen dengan 2
void multiply2(int *elem) {
    *elem *= 2;
}

// Fungsi membalikkan digit bilangan
void reverseEach(int *elem) {
    int num = *elem;
    int reversed = 0;
    while (num != 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    *elem = reversed;
}

// Fungsi menjumlahkan digit bilangan
void sumDigit(int *elem) {
    int num = *elem;
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    *elem = sum;
}

int main() {
    List myList;
    list_init(&myList);

    // Tambahkan elemen: [1, 2, 3, 4, 5]
    for (int i = 1; i <= 5; i++) {
        list_append(&myList, i*3);
    }

    printf("Isi list awal: ");
    forEachElement(&myList, printElement); // [1 2 3 4 5]
    printf("\n");

    printf("Setelah dikali 2: ");
    forEachElement(&myList, multiply2);   // [2 4 6 8 10]
    forEachElement(&myList, printElement);
    printf("\n");

    printf("Setelah dibalik: ");
    forEachElement(&myList, reverseEach); // [2 4 6 8 1]
    forEachElement(&myList, printElement);
    printf("\n");

    printf("Setelah dijumlah digitnya: ");
    forEachElement(&myList, sumDigit);    // [2 4 6 8 1]
    forEachElement(&myList, printElement);
    printf("\n");

    return 0;
}