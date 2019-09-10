#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/* Sorts an array by using insertion sort

   param an array with int values
   param the length of the array */
void insertion_sort(int *a, int n) {
    int p, key, temp;
    /* Starts at position 1 and goes through the array */
    for (p = 1; p < n; p++){
        /* Pulls out the value at p and goes back through the array */
        for (key = p; key > 0; key--){
            /* If there is a smaller value, swap them around */
            if (a[key] < a[key-1]){
                temp = a[key];
                a[key] = a[key-1];
                a[key-1] = temp;
            }
        }
    }
}

int main(void) {
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    /* Starts the time check and runs the insertion sort algorithm */
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
