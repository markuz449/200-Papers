#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    /* variable declarations */
    int i = 0;
    int f = 0;
    int g = 1;
    int temp = 0;
    int count = 0;
    /* a familiar "for loop" that iterates 40 times */
    for (i = 0; i < 40; i++) {
        printf("%d\n", g); /* printing the fibonacci numberh */
        temp = g;
        g = g + f;
        f = temp;
        count++;
        if (count == 5) {
            printf("\n");
            count = 0;
        }  
    }
    return EXIT_SUCCESS; /* defined in stdlib.h */
}
