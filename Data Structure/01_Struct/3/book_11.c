/*
# Task
    At a school's bazaar, activities were divided into stalls. At the close of the bazaar,
    the manager of each stall submitted information to the principal consisting of
    the name of the stall, the income earned, and its expenses. Here's some sample data:
        Games 2300.00 1000.00
        Sweets 900.00 1000.00
    Using structure to hold a stall's data, write a program to read the data and print
    a report consisting of the stall name and net income (income - expenses), in order of
    decreasing net income (that is , with the most profitable stall first and the least profitable stall last).
    In addition, print the number of stalls, the total profit or loss of the bazaar,
    and the stall(s) that made the most profit. Assume that a line containing xxxxxx only ends the data.
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 64 // max length of athlete's names
#define MAXSTALLS 256 // max number of stalls
#define FILENAME "bazaar.txt"

typedef struct {
    float income;
    float expenses;
    char name[MAXNAME + 1];
} Data;

unsigned short read(Data bzr[]) {
    FILE *bazaar = fopen(FILENAME, "r");
    if(bazaar == NULL) {
        perror("error opening long jump data");
        exit(-1);
    }

    char buffer[MAXNAME + 32];
    unsigned short turn = 0;
    char *token;
    // using " " as a delimiter

    while(fgets(buffer, MAXNAME + 32, bazaar) != NULL) {
        if(strcmp(buffer, "xxxxxx") == 0) break;

        token = strtok(buffer, " ");
        strncpy(bzr[turn].name, token, MAXNAME);
        
        token = strtok(NULL, " ");
        bzr[turn].income = strtof(token, NULL);
        
        token = strtok(NULL, " ");
        bzr[turn].expenses = strtof(token, NULL);
        
        turn++;
    }

    fclose(bazaar);
printf("%f\n", bzr[0].income);
printf("%f\n", bzr[1].income);
    return turn;
}

int compare(const void *a, const void *b) { // a function for "quicksort" in descending order
    Data *stall1 = (Data*)a;
    Data *stall2 = (Data*)b;

    // compare by distance (descending order)
    if(stall2->income - stall2->expenses > stall1->income - stall1->expenses) {
        return 1;
    }
    if(stall2->income - stall2->expenses < stall1->income - stall1->expenses) {
        return -1;
    }

    // if distances are the same, compare alphabetically by name (ascending order)
    return strcmp(stall1->name, stall2->name);
}

int main () {
    Data stall[MAXSTALLS] = {0};
    
    unsigned short number_of_stall = read(stall);
    qsort(stall, number_of_stall, sizeof(Data), compare);

    unsigned short order = 1;
    unsigned short same_cnt = 0; // if two or more stalls made the same profit
    unsigned short most_profit_stalls = 0;
    float total_bazaar_income = 0;


    // output the sorted data
    puts("net income report:");
    for (unsigned short i = 0; i < number_of_stall; i++) {
        if(order == 1) most_profit_stalls++;

        if(stall[i].income - stall[i].expenses == stall[i+1].income - stall[i+1].expenses) {
            printf("%d ", order);
            same_cnt++;
        } else {
            printf("%d ", order);
            order++;
            order += same_cnt;
            same_cnt = 0;
        }
        
        printf("%s %.3f\n", stall[i].name, stall[i].income - stall[i].expenses);
        total_bazaar_income += (stall[i].income - stall[i].expenses);
    }
    printf("number of stalls: %d\n", number_of_stall);
    printf("total bazaar profit/loss: %.3f\n", total_bazaar_income);
    puts("stall that made the most profit :");
    for (unsigned short i = 0; i < most_profit_stalls; i++) {
        printf("%s %.3f\n", stall[i].name, stall[i].income - stall[i].expenses);
    }
    
    return 0;
}