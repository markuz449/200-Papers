#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 10000

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void insertion_sort(char **wordlist, int n) {
    int p, key, ret;
    char *temp;

    for (p = 1; p < n; p++){
        for (key = p; key > 0; key--){
            ret = strcmp(wordlist[key], wordlist[key-1]);
            if (ret < 0){
                temp = wordlist[key];
                wordlist[key] = wordlist[key-1];
                wordlist[key-1] = temp;
            }
        }
    }
}

int main(void) {
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words;
    int i;
    int j;
    
    num_words = 0;
    while (num_words < ARRAY_LEN && 1 == scanf("%79s", word)) {
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    insertion_sort(wordlist, num_words);
    
    for (j = 0; j < num_words; j++){
        printf("%s\n", wordlist[j]);
    }
    
    for (i = 0; i < num_words; i++) {
        free(wordlist[i]);
    }
    
    return EXIT_SUCCESS;
}