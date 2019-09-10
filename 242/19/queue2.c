#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "mylib.h"

typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length
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
        q->head++;
    } else {
        q->items[(q->head + q->num_items) % q->capacity] = item;
        q->head = 0;
    }
    q->num_items ++;
    if (q->num_items > q->capacity){
        q->num_items = q->capacity;
    }
}

double dequeue(queue q){
    double dequeue_result = 0;
    if (q->head <= 0){
        q->head = q->capacity;
    }
    q->items[q->head - 1] = 0.0;
    q->head--;
    q->num_items--;
    return dequeue_result;
}

void queue_print(queue q){
    int i;
    printf("Num   Value\n");
    for (i = 0; i < q->capacity; i++){
        printf("%d     %.4f\n", i, q->items[i]);
    }
}

int queue_size(queue q){
    int i, size = 0;
    for(i = 0; i < q->capacity; i++){
        if (q->items[i] != 0.0){
            size++;
        }
    }
    return size;
}

queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
