#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};

htable htable_new(int capacity){
    int i;
    htable h = emalloc(sizeof *h);
    h->capacity = capacity;
    h->num_keys = 0;
    h->keys = emalloc(h->capacity * sizeof h->keys[0]);
    
    for(i = 0; i < capacity; i++){
        h->keys[i] = "";
    }
    return h;
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
    return i_key % h->capacity;
}

int htable_insert(htable h, char *str){
    int count;
    unsigned int tag;
    int size = strlen(str);

    /* if full return 0*/
    if (h->capacity == h->num_keys){
        return 0;
    } else {
        /* otherwise find tag location*/
        tag = htable_word_to_int(str);
        tag = htable_hash(h, tag);
        
        count = 0;
        while(strcmp(h->keys[tag], "") != 0 && count < h->capacity &&
              strcmp(h->keys[tag], str)  != 0){

            count++;    
            if (tag < (unsigned int)h->capacity - 1){
                tag++;
            } else{
                tag = 0;
            }             
        }
        if((strcmp(h->keys[tag], "") != 0) &&
           strcmp(h->keys[tag], str) == 0){
        }
        
        if(strcmp(h->keys[tag], "") == 0){
            /* set string to position tag*/
            h->keys[tag] = emalloc((size + 1)* sizeof (char));
            strcpy(h->keys[tag], str);
            h->num_keys++;
        }   
    }
    return tag;
}

void htable_print(htable h, FILE *stream){
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}

void htable_free(htable h){
    int i;
    for(i = 0; i < h->capacity; i++){
        if(strcmp(h->keys[i], "") != 0){
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h);
}
