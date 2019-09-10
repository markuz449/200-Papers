#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

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

queue queue_new() {
    queue q = emalloc(sizeof *q);
    q->first = NULL;
    q->last = NULL;
    q->length = 0;
    return q;
}

void enqueue(queue q, double item) {
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

double dequeue(queue q) {
    double result;
    q_item temp;
    if (q->length != 0){
        result = q->first->item;
        temp = q->first;
        if (q->first->next != NULL){
            q->first = q->first->next;
        }
        free(temp);
        q->length--;
        return result;
    }
    return 0.0;
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
    q_item i = q->first;
    while (i != NULL){
        printf("%.2f\n", i->item);
        i = i->next;
    }
}

void queue_print_info(queue q) {
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q) {
    return q->length;
}

void queue_free_aux(q_item i) {
    free(i);
}

queue queue_free(queue q) {
    int i;
    q_item temp;
    for (i = 0; i < q->length; i++){
        temp = q->first->next;
        queue_free_aux(q->first);
        q->first = temp;
    }
    free(q);
    return NULL;
}
