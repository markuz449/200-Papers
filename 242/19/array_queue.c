#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "mylib.h"

struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new(){
    int i;
    queue result = emalloc(sizeof *result);
    result->head = 0;
    result->capacity = 5;
    result->num_items = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);

    for (i = 0; i < result->capacity; i++){
        result->items[i] = 0.0;
    }
    return result;
}

void enqueue(queue q, double item){   
    if (q->num_items < q->capacity){
        q->items[(q->head + q->num_items) % q->capacity] = item;
        q->num_items ++;
        q->head++;
    }
}

double dequeue(queue q){
    double dequeue_result = q->items[q->head];
    if (q->num_items > 0){
        q->head--;
        q->num_items--;
        return dequeue_result;
    } else {
        return 0;
    }
}

void queue_print(queue q){
    int i;
    printf("Num   Value\n");
    for (i = 0; i < q->capacity; i++){
        printf("%d     %.4f\n", i, q->items[i]);
    }
}

int queue_size(queue q){
    return 0;
}

queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
