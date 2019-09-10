#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void insertion_sort(int *a, int n) {
    int p, key, temp;
    
    for (p = 1; p < n; p++){
        for (key = p; key > 0; key--){
            if (a[key] < a[key-1]){
                temp = a[key];
                a[key] = a[key-1];
                a[key-1] = temp;
            }
        }
    }
}

static void array_print(int *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

int main(void) {
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = emalloc(capacity * sizeof my_array[0]);
    
    while (1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = erealloc(my_array, capacity * sizeof my_array[0]);
        }
        my_array[itemcount++] = item;
    }

    insertion_sort(my_array, itemcount);
    array_print(my_array, itemcount);
    free(my_array);
    
    return EXIT_SUCCESS;
}
