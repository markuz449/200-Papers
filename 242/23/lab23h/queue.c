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
    int default_size = 7;
    queue result = emalloc(sizeof *result);
    result->head = 0;
    result->capacity = default_size;
    result->num_items = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);

    for (i = 0; i < result->capacity; i++){
        result->items[i] = 0.0;
    }
    return result;
}

void enqueue(queue q, double item){   
    if (q->num_items < q->capacity){
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q){
    double dequeue_result;
    if (q->num_items > 0){
        
        dequeue_result = q->items[q->head];
        /*q->items[q->head % q->capacity] = 0.0;*/
        q->num_items--;
        q->head++;
        q->head = q->head % q->capacity;
        return dequeue_result;
    }
    return 0.0;
}

void queue_print(queue q){
    int i;
    for (i = q->head; (i - q->head) < q->num_items; i++){
        printf("%.2f\n", q->items[i % q->capacity]);
    }
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q){
    return q->num_items;
}

queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
