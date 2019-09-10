#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/* Sorts an array by using selection sort

   param an array with int values
   param the length of the array */
void selection_sort(int *a, int n) {
    int p, i, index, temp;
    /* For loop which loops through the whole array */
    for (p = 0; p < n-1; p++){
        index = p; /* Sets the smallest value to p */
        /* Runs through the array a second time from p+1 */
        for (i = p + 1; i < n; i++){
            /* If there is a smaller value, set the new smallest */
            if (a[i] < a[index]){
                index = i;
            }
        }
        /* Swp the vaue at p with the smallest value */
        temp = a[index];
        a[index] = a[p];
        a[p] = temp;
    }
}

int main(void) {
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    /* Starts the time check and runs the selection sort algorithm */
    start = clock();
    selection_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
