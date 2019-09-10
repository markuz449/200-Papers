#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void merge (int *a, int *workspace, int len){
    int i = 0;
    int j = len / 2;
    int w = 0;

    while (i < len/2 && j < len){
        if (a[i] < a[j]){
            workspace[w++] = a[i++];
        } else {
            workspace[w++] = a[j++];
        }
    }
    while (i != (len / 2)){
        workspace[w++] = a[i++];
    }
    while (j != len){
        workspace[w++] = a[j++];
    }
    
}

void mergeSort (int *nums, int *w, int n){
    int count;
    if (n < 2){
        return;
    }
    mergeSort(nums, w, (n / 2));
    mergeSort((nums + (n / 2)), w, (n-(n / 2)));
    merge(nums, w, n);

    for (count = 0; count < n; count++){
        nums[count] = w[count];
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
    int workspace[f->capacity];
    mergeSort(f->items, workspace, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
}
