#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequency;
    char **keys;
};

htable htable_new(int capacity){
    int i;
    htable result = emalloc(sizeof *result);
    result->capacity = capacity;
    result->num_keys = 0;
    
    result->frequency = emalloc(result->capacity * sizeof result->frequency[0]);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    
    for(i = 0; i < capacity; i++){
        result->frequency[i] = 0;
        result->keys[i] = "\0";
    }
    return result;
}

void htable_free(htable h){
    int i;
    for(i = 0; i < h->num_keys; i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->frequency);
    free(h);
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    
    return result;
}

int htable_insert(htable h, char *str){
    int count;
    unsigned int tag;
    int size = strlen(str);

    /* if full return 0*/
    if (h->capacity == h->num_keys){
        printf("full");
        return 0;
    } else {
        /* otherwise find tag location*/
        tag = htable_word_to_int(str);
        tag = tag%h->capacity;
        printf("tag: %d\n", tag);
        
        count = 0;
        printf("%s\n", h->keys[tag]);
        while(strcmp(h->keys[tag], "") != 0 && count < h->capacity &&
              strcmp(h->keys[tag], str)  != 0){
            count++;
            printf("s: %d\n", count);
                
            if (tag < h->capacity - 1){
                tag++;
            } else{
                tag = 0;
            }             
        }
        
        if((strcmp(h->keys[tag], "") != 0) &&
           strcmp(h->keys[tag], str) == 0){
            printf("%d\n", strcmp(h->keys[tag], str));
        }
        
        printf("new tag: %d\n", tag);
        
        if(strcmp(h->keys[tag], "") == 0){
            /* set string to its key position*/
            h->keys[tag] = emalloc((size + 1)* sizeof h->keys[0][0]);
            strcpy(h->keys[tag], str);
        }
        h->frequency[tag]++;    
    }
    return h->frequency[tag];
}

void htable_print(htable h, FILE *stream){
    int i;
    
    stream = fopen("print.txt", "w");

    if (stream == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    
    for(i = 0; i < h->capacity; i++){
        if(strcmp(h->keys[i], "") != 0){
            printf("word: %s\n", h->keys[i]);
            fprintf(stream, "word: %s\n", h->keys[i]);
        }
    }
    fclose(stream);
}

int htable_search(htable h, char *str){
    int coll = 0;
    unsigned int tag = htable_word_to_int(str);
    tag = tag%h->capacity;

    while(strcmp(h->keys[tag],"") != 0 && coll < h->capacity &&
          strcmp(h->keys[tag], str)  != 0){
        coll++;
        if(tag < h->capacity - 1){
            tag++;
        }else{
            tag = 0;
        }
    }
    if (h->capacity == coll){
        return 0;
    }else{
        return h->frequency[tag];
    }
    
}

