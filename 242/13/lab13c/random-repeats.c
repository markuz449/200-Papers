#include <stdio.h>
#include <stdlib.h>

void display_repeats(int *a, int size){
    int *repeat_record = malloc(size * sizeof repeat_record[0]);;
    int i, j, count;

    for (count = 0; count < size; count++){
        repeat_record[count] = 0;
    }
    
    for (i = 0; i < size; i++){
        int temp = a[i];
        repeat_record[temp]++;
    }

    for (j = 0; j < size; j++){
        if (repeat_record[j] > 1){
            printf("%d occurs %d times\n", j, repeat_record[j]);
        }
    }
    free(repeat_record);
}
 

int main(void) {
    int array_size = 0;
    int *my_array = NULL;
    int i = 0;
    
    printf("Enter the size of the array:\n");
    scanf("%d", &array_size);
    
    my_array = malloc(array_size * sizeof my_array[0]);
    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < array_size; i++) {
        my_array[i] = rand() % array_size;
    }
    printf("What's in the array:\n");
    
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    display_repeats(my_array, array_size);
    
    free(my_array);
    
    return EXIT_SUCCESS;
}
