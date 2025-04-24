/*
#Task
    a binary search tree contains integers. For each of the following sequences, state whether  
    it could be the sequence of values examined in searching for the number 36. If it cannot, 
    state why.
            7 25 42 40 33 34 39 36
            92 22 91 24 89 20 35 36
            95 20 90 24 92 27 30 36
            7 46 41 21 26 39 37 24 36
#
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int target = 36, sequence_list[4][9] = {
        {7, 25, 42, 40, 33, 34, 39, 36},
        {92, 22, 91, 24, 89, 20, 35, 36},
        {95, 20, 90, 24, 92, 27, 30, 36},
        {7, 46, 41, 21, 26, 39, 37, 24, 36}
    };

    int j, min, max, inv_val, inv_idx;
    _Bool exc_mn, exc_mx, valid; // * to check if the value exceed min or max 

    for (int i = 0; i < 4; i++) {
        j = 0, exc_mn = 0, exc_mx = 0, valid = 1;

        printf("Sequence: ");
        while(sequence_list[i][j] != target) {
            printf("%d ", sequence_list[i][j]); j++;
        }
        printf("%d\n", sequence_list[i][j]);

        for (j = 0; sequence_list[i][j] != target; j++) {
            if((exc_mn && sequence_list[i][j] < min) || (exc_mx && sequence_list[i][j] > max)) {
                inv_val = sequence_list[i][j];
                inv_idx = j + 1;
                valid = 0;
                break;
            }

            if(sequence_list[i][j + 1] > sequence_list[i][j]) {
                exc_mn = 1;
                min = sequence_list[i][j];
            }
            
            if(sequence_list[i][j + 1] < sequence_list[i][j]) {
                exc_mx = 1;
                max = sequence_list[i][j];
            }
        }

        if(valid) printf("Sequence is valid\n\n");
        else printf("Sequence is invalid due to the value of %d at position %d is in the wrong order\n\n", inv_val, inv_idx);
    }
    puts("The error occurs because if the sequence order is inserted into a bst, every node must have only one child, either left or right.");
}