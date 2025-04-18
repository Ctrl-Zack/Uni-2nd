/*
# Task
    Two Words are anagrams if one word can be formed by rearranging all the letters of the other word,
    for example treason, senator. A word is represented as a linked list with one letter per node of the list.
    Write a function that, given w1 and w2 each pointing to a word of lowercase letters, returns 1 if the words
    are anagrams and 0 they are not. Base your algorithm on the following:
    for each leter in w1, search w2 for it; if found, delete it and continue. Otherwise, return 0.
#
*/

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  

struct Node {
    char value;
    struct Node *next;
};
typedef struct Node Node_t;

Node_t *create_new_node(char letter) {
    Node_t *ptr_to_new_node = (Node_t *)malloc(sizeof(Node_t));
    if(ptr_to_new_node != NULL) {
        ptr_to_new_node->value = letter;
        ptr_to_new_node->next = NULL;
    }
    return ptr_to_new_node;
}

void insert_front(Node_t **head, char letter) {
    Node_t *newNode = create_new_node(letter);
    if (newNode != NULL) {
        newNode->next = *head;
        *head = newNode;
    }
}

void create_linked_list(Node_t **head, const char *word) {
    for (int i = 0; i < strlen(word); i++) {
        insert_front(head, *(word + i));
    }
}

// ? void print_list(Node_t *head) {
// ?   Node_t *ptr_travers = head;
// ?    while (ptr_travers != NULL) {
// ?        printf("%c - ", ptr_travers->value);
// ?        ptr_travers = ptr_travers->next;
// ?    }
// ?    printf("\n");
// ?}


Node_t *remove_letter(Node_t *head, const char letter, _Bool *found) {
    if (head == NULL) {
        return NULL;
    }
    
    Node_t *cur = head;
    Node_t *prev = NULL;

    while (cur != NULL) {
        if(cur->value == letter) {
            if(prev == NULL) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            *found = 1;
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    return head;
}

int count_nodes(Node_t *head) {
    int cnt = 0;
    Node_t *cur = head;
    while (cur != NULL) {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

_Bool is_anagram(Node_t *w1, Node_t *w2) {
    if (count_nodes(w1) != count_nodes(w2)) {
        return 0;
    }
        
    Node_t *ptr_travers = w1;
    _Bool result = 1;
    
    while (ptr_travers != NULL) {
        _Bool found = 0;
        w2 = remove_letter(w2, ptr_travers->value, &found);
        if (!found) {
            result = 0;
            break;
        }
        ptr_travers = ptr_travers->next;
    }
    
    return w2 == NULL ? 1 : 0;
}

int main() {
    Node_t *head1 = NULL;
    Node_t *head2 = NULL;
    
    char buffer[256];

    scanf(" %s", buffer);
    create_linked_list(&head1, buffer);
    
    scanf(" %s", buffer);
    create_linked_list(&head2, buffer);

    printf("%s\n", is_anagram(head1, head2) == 1 ? "are anagrams" : "not anagrams");

    return 0;
}