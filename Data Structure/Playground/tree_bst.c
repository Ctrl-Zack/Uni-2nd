int global_positives = 0;

typedef struct list {
    struct list *next;
    double val;
} * list;

void count_positives(list l) {
    list p;
    for (p = l; p; p = p->next) {
        if(p->val > 0.0)
            ++global_positives;
    }   
}