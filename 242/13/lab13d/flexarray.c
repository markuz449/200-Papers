#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void insertion_sort(int *a, int n) {
    int p, j, key, temp;
    for (p = 1; p < n; p++){
        for (key = p; key > 0; key--){
            if (a[key] < a[key-1]){
                temp = a[key];
                a[key] = a[key-1];
                a[key-1] = temp;
            }
        }
        if (p == ((n-1)/2)){
            for (j = 0; j < n; j++) {
                fprintf(stderr, "%d\n", a[j]);
            }
        }
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
    insertion_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}