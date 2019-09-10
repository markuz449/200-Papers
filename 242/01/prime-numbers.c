#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime (int candidate) {
    int i;
    for (i = 2; i < candidate; i++){
        if (candidate % i == 0){
            return 0;
        }
        return 1;
    }
}

int main(void) {
    /* variable declarations */
    int candidate = 2;
    int num_printed = 0;
    while (num_printed < 100){
        if (is_prime (candidate)) {
            printf ("%d: prime number %d\n",  num_printed, candidate);
            num_printed ++;
        }
        candidate ++;
    }
    return EXIT_SUCCESS; /* defined in stdlib.h */
}
