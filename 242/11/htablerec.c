#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htablerec.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequencies;
    char **keys;
};

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

htable htable_new (int capacity){
    int i;
    htable newTable = emalloc(sizeof *newTable);
    newTable->capacity = capacity;
    newTable->num_keys = 0;
    newTable->frequencies = emalloc(newTable->capacity * sizeof newTable->frequencies[0]);
    newTable->keys = emalloc(newTable->capacity * sizeof newTable->keys[0]);
    for (i = 0; i < newTable->capacity; i++){
        /**newTable->keys[i] = emalloc(50 * sizeof newTable->keys[0]);**/
        newTable->frequencies[i] = 0;
        newTable->keys[i] = NULL;
    }
    return newTable;
}

int htable_insert (htable h, char *str){
    unsigned int hash;
    int count;
    printf("test 0\n");
    printf("%s\n", str);
    hash = htable_word_to_int(str);
    printf("\n");
    hash = hash % h->capacity;
    
    count = 0;

    
    if  (h->keys[hash] == NULL){
        h->keys[hash] = emalloc(strlen(str) + 1 * sizeof(h->keys[0][0]));
        strcpy(h->keys[hash], str);
        /**h->keys[hash] = str;**/
        h->frequencies[hash] = 1;
        h->num_keys += 1;
        return 1;
    } else if (h->keys[hash] == str){
        h->frequencies[hash] += 1;
        return h->frequencies[hash];
    } else {
        printf("test 3");
        while (h->keys[hash] != NULL || h->keys[hash] != str){
            hash++;
            count++;
            printf("test 4");

            if (h->keys[hash] == NULL){
                h->keys[hash] = str;
                h->frequencies[hash] = 1;
                h->num_keys += 1;
                return 1;
            } else if (h->keys[hash] == str){
                h->frequencies[hash] += 1;
                return h->frequencies[hash];
            }

            if (count > h->capacity){
                return 0;
            }
        }
    }
}

void htable_print (htable h, FILE *stream){
    int i;
    for (i = 0; i < h->capacity; i++){
        if (h->keys[i] != NULL){
            printf("%s\n", h->keys[i]);
        }
    }
}

void htable_free (htable h){
    int i;
    for (i = 0; i < h->capacity; i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->frequencies);
    free(h);
}


/*
int htable_search (htable h, char *str){
    return 1;
}
*/
