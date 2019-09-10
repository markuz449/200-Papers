#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
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

/**
 * Gets a single word from a given file stream and sets s to that word then
 * moves to the next word. Returns EOF if next word is not found.
 *
 * @param s the string to be set as the word.
 * @param limit the length of s.
 * @param stream the file stream to be read from.
 *
 * @return rither EOF if end-of-input was found or an int if the word was set
 * successfully.
 */
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}
