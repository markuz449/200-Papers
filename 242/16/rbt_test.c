#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

void print_key(char *s) {
    printf("%s, ", s); 
}

int main(void){
    int i;
    char *alf[26] = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h",
                     "j", "k", "l", "z", "x", "c", "v", "b", "n", "m"};

    
    rbt r = rbt_new();

    /*for (i = 0; i < 26; i++){
        r = rbt_insert(r, alf[i]);
        r = rbt_fix_root(r);
        }*/
        
    r = rbt_insert(r, "h");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "l");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "i");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "f");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "j");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "g");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "k");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "d");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "a");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "e");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "b");
    r = rbt_fix_root(r);
    r = rbt_insert(r, "c");
    r = rbt_fix_root(r);

    rbt_inorder(r, print_key);
    printf("\n");
    rbt_preorder(r, print_key);
    printf("\n");

    /*for (i = 0; i < 26; i++){
        i += 2;
        if (i > 25){
        } else {
            r = rbt_delete(r, alf[i]);
        }
        }*/

    /*r = rbt_delete(r, "d");*/

    rbt_inorder(r, print_key);
    printf("\n");
    rbt_preorder(r, print_key);
    printf("\n");

    r = rbt_free(r);
      
    return EXIT_SUCCESS;
}