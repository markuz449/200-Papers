#include <stdio.h>
#include <stdlib.h>
#include "htablerec.h"

int main(void) {
    char *word[100];
    int count = 0, capacity = 11;
    htable h = htable_new(capacity);
    
    while ((-1 != scanf("%s", word)) && (count < capacity)) {
        htable_insert (h, word);
        count++;
    }
    
    htable_print(h, stdout);
    htable_free(h);
    
    return EXIT_SUCCESS;
}
