#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int id;
    char pelapor[31];
    int prioritas;
    int timestamp;
} Laporan;

int ts = 1;

typedef struct node {
    Laporan L;
    struct node *next;
} Node_L;

typedef struct list_t {
    Node_L *_top;
    unsigned _size;
} LList;

void list_init(LList *list);
_Bool list_isEmpty(LList *list);
void list_push(LList *list, Laporan value);
void list_pop(LList *list);
Laporan list_top(LList *list);
_Bool search(LList *list, int id);

void list_init(LList *list) {
    list->_top = NULL;
    list->_size = 0;
}

_Bool list_isEmpty(LList *list) {
    return (list->_top == NULL);
}

void list_push(LList *list, Laporan value) {
    Node_L *temp = list->_top;
    Node_L *newNode = (Node_L*) malloc (sizeof(Node_L));
    newNode->L.id = value.id;
    strncpy(newNode->L.pelapor, value.pelapor, 31);
    newNode->L.prioritas = value.prioritas;
    newNode->L.timestamp = value.timestamp;
    newNode->next = NULL;

    if (list_isEmpty(list)) {
        list->_top = newNode;
        return;
    }

    if (value.prioritas < list->_top->L.prioritas) {
        newNode->next = list->_top;
        list->_top = newNode;
    } else {
        while (temp->next != NULL && temp->next->L.prioritas > value.prioritas && temp->next->L.timestamp < value.timestamp)
        temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void list_pop(LList *list) {
    if (!list_isEmpty(list)) {
        Node_L *temp = list->_top;
        list->_top = list->_top->next;
        free(temp);
    }
}

Laporan list_top(LList *list) {
    Laporan tmp = {-1, "", -1, -1};
    if (!list_isEmpty(list))
    return list->_top->L;
    else return tmp;
}

_Bool search(LList *list, int id) {
    Node_L *tmp = list->_top;
    while(tmp != NULL) {
        if(tmp->L.id == id) return 1;
        tmp = tmp->next;
    }
    return 0;
}

void Tambah_laporan_baru(LList *list) {
    Laporan baru;
    printf("id: ");
    scanf(" %d", &baru.id);
    if(search(list, baru.id)) {
        printf("id sudah dipakai\n");
        return;
    }
    printf("pelapor: ");
    scanf(" %31[^\n]", baru.pelapor);
    printf("prioritas: ");
    scanf(" %d", &baru.prioritas);
    baru.timestamp = ts++;

    list_push(list, baru);
}

void Proses_laporan(LList *list) {
    if(list_isEmpty(list)) return;
    printf("id: %d\n", list->_top->L.id);
    printf("pelapor: %s\n", list->_top->L.pelapor);
    printf("prioritas: %d\n", list->_top->L.prioritas);
    printf("timestamp: %d\n\n", list->_top->L.timestamp);
    list_pop(list);
}

void Tampilkan_semua_laporan_dalam_antrean(LList *list) {
    if(list_isEmpty(list)) return;
    Node_L *tmp = list->_top;
    
    while(tmp != NULL) {
        printf("id: %d\n", tmp->L.id);
        printf("pelapor: %s\n", tmp->L.pelapor);
        printf("prioritas: %d\n", tmp->L.prioritas);
        printf("timestamp: %d\n\n", tmp->L.timestamp);
        tmp = tmp->next;
    }
}

int main() {
    LList lp;
    list_init(&lp);

    char opt;
    
    puts("1. Tambah laporan baru");
    puts("2. Proses laporan (hapus dari list dan tampilkan datanya)");
    puts("3. Tampilkan semua laporan dalam antrean ");
    puts("4. Keluar dari program");
    
    while(scanf(" %c", &opt)) {
        if(opt == '1') { Tambah_laporan_baru(&lp); }
        if(opt == '2') { Proses_laporan(&lp); }
        if(opt == '3') { Tampilkan_semua_laporan_dalam_antrean(&lp); }
        if(opt == '4') { break; }

        puts("1. Tambah laporan baru");
        puts("2. Proses laporan (hapus dari list dan tampilkan datanya)");
        puts("3. Tampilkan semua laporan dalam antrean ");
        puts("4. Keluar dari program");
    }
}