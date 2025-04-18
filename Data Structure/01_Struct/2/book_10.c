/*
# Task
    A file contains the names and distances jumped by athletes
    in a long-jump competition. Using a structure to hold a name and distance
    (which is itself a structure as in 8), write a program to read the data
    and print a list of names and distance jumped in order of merit (best jumper first).
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CAPACITY 8 // the number of athletes
#define MAXNAME 64 // max length of athlete's names
#define FILENAME "long_jump.txt"

typedef struct {
    float dist;
    char name[MAXNAME + 1];
} Data;

unsigned short read(Data ath[]) {
    FILE *long_jump = fopen(FILENAME, "r");
    if(long_jump == NULL) {
        perror("error opening long jump data");
        exit(-1);
    }

    char buffer[MAXNAME + 32];
    unsigned short turn = 0;
    char *token;
    // using ; as a delimiter so that the name can contain space

    while(fgets(buffer, MAXNAME + 32, long_jump) != NULL) {        
        token = strtok(buffer, ";");
        strncpy(ath[turn % CAPACITY].name, token, MAXNAME);
        
        token = strtok(NULL, ";");
        ath[turn % CAPACITY].dist = fmax(strtof(token, NULL), ath[turn % CAPACITY].dist) ;
        
        turn++;
    }

    fclose(long_jump);

    return turn / CAPACITY;
}

int compare(const void *a, const void *b) { // a function for "quicksort" in descending order
    Data *athlete1 = (Data*)a;
    Data *athlete2 = (Data*)b;

    // compare by distance (descending order)
    if(athlete2->dist > athlete1->dist) {
        return 1;
    }
    if(athlete2->dist < athlete1->dist) {
        return -1;
    }

    // if distances are the same, compare alphabetically by name (ascending order)
    return strcmp(athlete1->name, athlete2->name);
}

int main () {
    Data athlete[CAPACITY] = {0};
    
    unsigned short round = read(athlete);
    qsort(athlete, CAPACITY, sizeof(Data), compare);

    unsigned short order = 1; // order of merit
    unsigned short same_cnt = 0; // if two or more athletes got the same score

    // output the sorted data
    printf("list of names and distance jumped in order of merit (%d rounds):\n", round);
    for (unsigned short i = 0; i < CAPACITY; i++) {
        if(athlete[i].dist == athlete[i+1].dist) {
            printf("%d ", order);
            same_cnt++;
        } else {
            printf("%d ", order);
            order++;
            order += same_cnt;
            same_cnt = 0;
        }
        printf("%s %.3f\n", athlete[i].name, athlete[i].dist);
    }
    
    return 0;
}