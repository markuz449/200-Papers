#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bstnode{
    char *key;
    bst left;
    bst right;
};

bst find_successor(bst b){
    b = b->right;
    while(b->left != NULL){
        b = b->left;
    }
    return b;
}

bst bst_new(){
    return NULL;
}

bst bst_insert(bst b, char *str){
    if (b == NULL){
        b = emalloc(3 * sizeof(b));
        b->key = (char *)emalloc(strlen(str) + 1 * sizeof(char));
        strcpy(b->key, str);
        b->left = bst_new();
        b->right = bst_new();
        return b;
    } else {
        if (strcmp(b->key, str) == 0){
            return b;
        } else if (strcmp(b->key, str) > 0){
            b->left = bst_insert(b->left, str);
        } else {
            b->right = bst_insert(b->right, str);
        }
        return b;
    }  
}

void bst_preorder(bst b, void f(char *str)){
    if (b == NULL){
        return;
    }
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

void bst_inorder(bst b, void f(char *str)){
    if (b == NULL){
        return;
    } 
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);
}

int bst_search(bst b, char *str){
    if (b == NULL){
        return 0;
    }else if(strcmp(b->key, str) == 0){
        return 1;
        /* return < 0 if b->key < str*/
    }else if(strcmp(b->key, str) > 0){
        return bst_search(b->left, str);
    }else{
        return bst_search(b->right, str);
    }
}

bst bst_free(bst b){
    if (b == NULL){
        return b;
    }
    b->left = bst_free(b->left);
    b->right = bst_free(b->right);
    free(b->key);
    free(b);
    return b;
}
