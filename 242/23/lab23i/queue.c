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
    int length;
};

void queue_free_aux(q_item i) {
    free(i);
}

queue queue_new(){
    queue result = emalloc(sizeof *result);
    result->length = 0;
    result->first = NULL;
    result->last = NULL;
    return result;
}

void enqueue(queue q, double item){   
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q){
    double dequeue_item;
    q_item temp;
    if (q->length == 0){
        return 0;
    }
    dequeue_item = q->first->item;
    temp = q->first;
    if (q->first->next != NULL){
        q->first = q->first->next;
    }
    free(temp);
    q->length--;
    return dequeue_item;
}

void queue_print(queue q){
    q_item i = q->first;
    while (i != NULL){
        printf("%.2f\n", i->item);
        i = i->next;
    }
}

void queue_print_info(queue q){
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q){
    return q->length;
}

queue queue_free(queue q){
    int i;
    int length = q->length;
    for (i = 0; i < length; i++){
        dequeue(q);
    }
    free(q);
    return NULL;
}
