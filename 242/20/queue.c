#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "mylib.h"

/**
 * Struct queue. The basic structure for a queue.
 *
 * Contents:
 *     @li items an array that holds the value of each item in the queue.
 *     @li head the value of where the queue is upto.
 *     @li capacity the maximum capacity that the queue can hold.
 *     @li num_items the number of how many items are in the queue.
 */
struct queue {
    int *items;
    int head;
    int capacity;
    int num_items;
};

/**
 * Creates a new queue with a specified size.
 *
 * @param size the maximum capacity that the queue will be able to hold.
 *
 * @return the created queue.
 */
queue queue_new(int size){
    int i;
    queue result = emalloc(sizeof *result);
    result->head = 0;
    result->capacity = size;
    result->num_items = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);

    for (i = 0; i < result->capacity; i++){
        result->items[i] = -1;
    }
    return result;
}

/**
 * Adds a value to the queue.
 *
 * @param q the queue that will have the item added to it.
 * @param item the value of the item that will be added.
 */
void enqueue(queue q, int item){   
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

/**
 * Removes an item from the queue and returns the value of the removed item.
 *
 * @param q the queue that will have an item removed.
 *
 * @return the value of the removed item.
 */
int dequeue(queue q){
    int dequeue_result;
    if (q->head <= 0){
        q->head = q->capacity;
    }
    q->head--;
    q->num_items--;

    dequeue_result = q->items[(q->head + q->num_items) % q->capacity];
    q->items[(q->head + q->num_items) % q->capacity] = -1;
    return dequeue_result;
}

/**
 * Prints the items currently in the queue.
 *
 * @param q the queue that will be printed.
 */
void queue_print(queue q){
    int i;
    printf("Num   Value\n");
    for (i = 0; i < q->capacity; i++){
        printf("%d     %d\n", i, q->items[i]);
    }
}

/**
 * Returns the current size of the queue.
 *
 * @param q the queue to be checked the size of.
 *
 * @return the size of the current queue.
 */
int queue_size(queue q){
    return q->num_items;
}

/**
 * Frees the memory allocated for the queue.
 *
 * @param q the queue that will be freed.
 *
 * @return the freed queue that will be null.
 */
queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
