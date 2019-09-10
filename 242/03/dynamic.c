#include <stdio.h>
#include <stdlib.h>

void display_repeats(int *a, int size){
    int *repeat_record;
    int i, j;

    repeat_record = malloc(size * sizeof repeat_record[0]);
    
    for (i = 0; i < size; i++){
        int temp = a[i];
        repeat_record[temp]++;
    }

    for (j = 0; j < size; j++){
        printf("Number: %d, Repeats: %d\n", j, repeat_record[j]);
    }

    free(repeat_record);
}
    

int main(void) {
    int array_size = 0;
    int *my_dynamic_array;
    int i = 0;
    
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);
    
    /* initialise the array to the appropriate size */
    my_dynamic_array = malloc(array_size * sizeof my_dynamic_array[0]);
    if (NULL == my_dynamic_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < array_size; i++) {
        my_dynamic_array[i] = rand() % array_size;
    }
    printf("What’s in the array:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_dynamic_array[i]);
    }
    printf("\n");

    display_repeats(my_dynamic_array, array_size);
    
    /* release the memory associated with the array */
    free(my_dynamic_array);
    
    return EXIT_SUCCESS;
}
