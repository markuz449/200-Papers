#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 5

void max_min(int *a, int n, int *max, int *min){
    int i;
    *max = a[0];
    *min = a[0];
    
    for (i = 0; i < n; i++) {
        if (a[i] >= *max){
            *max = a[i];
        }
        else if (a[i] < *min){
            *min = a[i];
        }
    }
}

int main(void) {
    int my_array[ARRAY_SIZE];
    int counter = 0;
    int biggest, smallest;
    
    while (counter < ARRAY_SIZE && 1 == scanf("%d", &my_array[counter])) {
        counter++;
    }

    max_min(my_array, ARRAY_SIZE, &biggest, &smallest);
    printf("max value is %d, min value is %d\n", biggest, smallest);
    
    return EXIT_SUCCESS;
}
