#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void print_key(char *s) {
    printf("%s, ", s); 
}

int main(void){
    int i;
    char *alf[26] = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h",
                     "j", "k", "l", "z", "x", "c", "v", "b", "n", "m"};
    
    bst b = bst_new();

    for (i = 0; i < 26; i++){
        b = bst_insert(b, alf[i]);
    }

    bst_inorder(b, print_key);
    printf("\n");
    bst_preorder(b, print_key);
    printf("\n");

    for (i = 0; i < 26; i++){
        i += 2;
        if (i > 25){
        } else {
            b = bst_delete(b, alf[i]);
        }
    }

    bst_inorder(b, print_key);
    printf("\n");
    bst_preorder(b, print_key);
    printf("\n");

    bst_free(b);
    
    return EXIT_SUCCESS;
}
