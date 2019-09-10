#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main(void){
    queue q = queue_new();

    enqueue(q, 5.23);
    enqueue(q, 2.4);
    enqueue(q, 4.4565);
    enqueue(q, 52.36);
    enqueue(q, 7.8);
    enqueue(q, 6.9);

    dequeue(q);
    dequeue(q);
    dequeue(q);
    
    queue_print(q);

    printf("Size of queue: %d\n", queue_size(q));

    queue_free(q);

    return EXIT_SUCCESS;
}
