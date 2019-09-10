#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

/**
 * Struct htablerec. The basic structure of the htable.
 *
 * Contents:
 *     @li capacity maximum size of the htable.
 *     @li num_keys current number of filled keys.
 *     @li frequency array holding the number of duplicate keys.
 *     @li keys array holding the key strings.
 *     @li stats array holding the number of collisions.
 *     @li method enum type either linear or double hashing.
 */
struct htablerec {
    unsigned int capacity;
    unsigned int num_keys;
    unsigned int *frequency;
    char **keys;
    unsigned int *stats;
    hashing_t method;
};

/**
 * Creates a new htable, allocating memory to each component of the htable.
 * Sets the inital values of the three arrays to their default values.
 * 
 * @param capacity sets the max capacity of the htable.
 * @param ht the hashing type, either double of linear hashing.
 *
 * @return result the resultant htable.
 */
htable htable_new(int capacity, hashing_t ht){
    int i;
    htable result = emalloc(sizeof *result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->method = ht;
    
    result->frequency = emalloc(result->capacity *
                                sizeof result->frequency[0]);
    result->stats = emalloc(result->capacity * sizeof result->stats[0]);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    
    for(i = 0; i < capacity; i++){
        result->frequency[i] = 0;
        result->stats[i] = 0;
        result->keys[i] = "\0";
    }
    return result;
}

/**
 * Free's all of the htable's mallocated components the free's the htable.
 * 
 * @param h the htable to be freed.
 */
void htable_free(htable h){
    unsigned int i;
    for(i = 0; i < h->capacity; i++){
        if(strcmp(h->keys[i], "") != 0){
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h->frequency);
    free(h->stats);
    free(h);
}

/**
 * Calculates the step added to the hash key when double hashing.
 * not used when linear probing.
 *
 * @param h the htable involved.
 * @param i_key the current hash key.
 *
 * @return the step to be added to the key.
 */
static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

/**
 * Given a character string calculates the hash value of the string.
 *
 * @param word the string the hash value is calculated from.
 *
 * @return the hash value.
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    
    return result;
}

/**
 * Searches through the htable using either linear probing or double hashing
 * depending on the htable's method variable.
 *
 * @param h the htable to be searched.
 * @param str the string we are trying to find in the htable.
 *
 * @return the frequency of the key if found or 0 if not found.
 */
int htable_search(htable h, char *str){
    unsigned int coll = 0;
    unsigned int step;
    unsigned int tag = htable_word_to_int(str);
    step = htable_step(h, tag);
    tag = tag%h->capacity;
    
    if (h->method == 0){
        while(strcmp(h->keys[tag],"") != 0 && coll < h->capacity &&
              strcmp(h->keys[tag], str)  != 0){
            coll++;
            if (tag < h->capacity - 1){
                tag++;
            } else{
                tag = 0;
            }
        }   
    } else {
        while(strcmp(h->keys[tag],"") != 0 && coll < h->capacity &&
              strcmp(h->keys[tag], str)  != 0){
            coll++;
        
            tag += step;
            if (tag > h->capacity -1){
                tag -= h->capacity;
            };
        }
    }
    
    if (h->capacity == coll){
        return 0;
    }else{
        return h->frequency[tag];
    }
    
}

/**
 * Inserts a key either using linear probing or double hashing depending
 * on the htable's method vairable. Updates the relevant htable components.
 * If the key is already in the array, updates the frequency and returns.
 * If the capacity is full and the key is not found, return 0.
 *
 * @param h the htable to insert into.
 * @param str the string to insert.
 *
 * @return the frequency of the key at it's position, or 0 if not inserted.
 */
int htable_insert(htable h, char *str){
    unsigned int count;
    unsigned int tag, step;
    int size = strlen(str);
    /* if full return 0*/
    if (h->capacity == h->num_keys && 0 == htable_search(h, str)){
        return 0;
    } else {
        /* otherwise find tag location*/
        tag = htable_word_to_int(str);
        step = htable_step(h, tag);
        tag = tag%h->capacity;
        
        if (h->method == 0){
            count = 0;
            while(strcmp(h->keys[tag], "") != 0 && count < h->capacity &&
                  strcmp(h->keys[tag], str)  != 0){
                count++;
                if (tag < h->capacity - 1){
                    tag++;
                } else{
                    tag = 0;
                }             
            }
        } else {
            count = 0;
            while(strcmp(h->keys[tag], "") != 0 && count < h->capacity &&
                  strcmp(h->keys[tag], str)  != 0){
                count++;
                tag += step;
                if (tag > h->capacity -1){
                    tag -= h->capacity;
                }
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
        if(h->frequency[tag] == 0){
            h->stats[h->num_keys - 1] = count;
        }
        h->frequency[tag]++;    
    }
    return h->frequency[tag];
}

/**
 * Prints out all keys that are not null using the given print function.
 *
 * @param h the htable to print from.
 * @param f(int freq, char *word) the function used to print the table.
 */
void htable_print(htable h, void f(int freq, char *word)){
    unsigned int i;

    for(i = 0; i < h->capacity; i++){
        if (h->frequency[i] != 0){
            f(h->frequency[i], h->keys[i]);
        }
    }
        
}

/**
 * Prints the entire htable one line at a time including the lines array
 * location, frequency, stats, and key.
 *
 * @param h the htable to print.
 */
void htable_print_entire_table(htable h){
    unsigned int i;
    for(i = 0; i < h->capacity; i++){
        fprintf(stderr, "%5d %5d %5d   %s\n",
                i, h->frequency[i], h->stats[i], h->keys[i]);

    }
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    unsigned int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    unsigned int max_collisions = 0;
    unsigned int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
    fprintf(stream, "-----------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream,
            "-----------------------------------------------------\n\n");
}
