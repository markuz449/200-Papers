#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

/**
 * Allocates memory to the given parameter. If memory fails to be allocated
 * prints out an error message.
 *
 * @param s the parameter that needs memory allocated to it.
 */
void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
