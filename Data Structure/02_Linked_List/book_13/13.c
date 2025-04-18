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

struct Node_t {
    char digit;
    struct Node_t *next;
};
typedef struct Node_t Node_t;

struct L_list {
    unsigned _size;
    Node_t *_head;
};
typedef struct L_list L_list;

void list_init(L_list *list);
_Bool list_isEmpty(L_list *list);
void list_pushFront(L_list *list, char digit);
void list_add(L_list *list1, L_list *list2, L_list *ans);
void list_printElement(L_list *list);
void list_getNum(L_list *list);


void list_init(L_list *list) {
    list->_head = NULL;
    list->_size = 0;
}

_Bool list_isEmpty(L_list *list) {
    return (list->_head == 0);
}

void list_pushFront(L_list *list, char nDigit) {
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    if(newNode) {
        list->_size++;
        newNode->digit = nDigit;

        if(list_isEmpty(list))
            newNode->next = NULL;
        else
            newNode->next = list->_head;
        list->_head = newNode;
    }
}

void list_add(L_list *list1, L_list *list2, L_list *ans) {
    Node_t *tmpList1 = list1->_head;
    Node_t *tmpList2 = list2->_head;
    
    short carry = 0;
    short sum;
    while(tmpList1 != NULL || tmpList2 != NULL || carry != 0) {
        sum = carry;

        if(tmpList1 != NULL) {
            sum += (tmpList1->digit - '0');
            tmpList1 = tmpList1->next;
        }

        if(tmpList2 != NULL) {
            sum += (tmpList2->digit - '0');
            tmpList2 = tmpList2->next;
        }

        carry = sum / 10;
        list_pushFront(ans, (char)(sum % 10 + '0'));
    }
}

void list_printElement(L_list *list) {
    Node_t *tmp = list->_head;
    while(tmp != NULL) {
        printf("%c", tmp->digit);
        tmp = tmp->next;
    }
    putchar('\n');
}

void list_getNum(L_list *list) {
    char tmp;
    do {
        scanf("%c", &tmp);
        if(tmp != '\n')
            list_pushFront(list, tmp);
    } while(tmp != '\n');
}

int main() {
    L_list num1;
    L_list num2;
    L_list ans;

    list_init(&num1);
    list_init(&num2);
    list_init(&ans);

    puts("Enter first number: ");
    list_getNum(&num1);
    puts("Enter Second number: ");
    list_getNum(&num2);
    
    // list_printElement(&num1);
    // list_printElement(&num2);
    
    list_add(&num1, &num2, &ans);
    puts("Answer: ");
    list_printElement(&ans);

    return 0;
}