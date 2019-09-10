#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

#define MAX 11

int main(void){
    char word1[4] = "dog";
    char word2[4] = "dog";
    char word3[4] = "cat";
    char word4[6] = "mouse";
    char word5[6] = "puppy";
    char word6[4] = "pig";
    char word7[4] = "pug";
    char word8[9] = "parrot?";
    char word9[5] = "bird";
    htable h = htable_new(MAX);
    FILE *f1;

    /*printf("%s, ", word1);
      printf("%s\n", word2);*/
    
    printf("fq: %d\n",htable_insert(h, word1));
    printf("fq: %d\n",htable_insert(h, word2));
    printf("fq: %d\n",htable_insert(h, word3));
    printf("fq: %d\n",htable_insert(h, word4));
    printf("fq: %d\n",htable_insert(h, word5));
    printf("fq: %d\n",htable_insert(h, word6));
    printf("fq: %d\n",htable_insert(h, word7));
    printf("fq: %d\n",htable_insert(h, word8));
    printf("fq: %d\n",htable_insert(h, word9));

    printf("Word found bitch, at freq: %d\n ", htable_search(h, word2));

    htable_print(h, f1);
    
    htable_free(h);
    printf("free\n");
    return EXIT_SUCCESS;
}
