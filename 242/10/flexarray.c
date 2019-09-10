#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void quicksort (int *nums, int first, int last){ 
    int i, j, pivot, temp;

    if (first < last){
        pivot = first;
        i = first;
        j = last;
        
        while (i < j){
            while (nums[i] <= nums[pivot] && i < last){
                i++;
            }
            while (nums[j] > nums[pivot]){
                j--;
            }

            if (i < j){
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;    
            }           
        }
        temp = nums[pivot];
        nums[pivot] = nums[j];
        nums[j] = temp;
        
        quicksort (nums, first, j - 1);
        quicksort (nums, j + 1, last);
    }
}
    
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f) {
    /* int workspace[f->capacity];*/
    quicksort(f->items, 0, f->itemcount - 1);
}

void flexarray_free(flexarray f) {
    free(f->items);
}
