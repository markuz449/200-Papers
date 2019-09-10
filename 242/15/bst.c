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

bst bst_free(bst b){
    if (b == NULL){
        return b;
    }
    b->left = bst_free(b->left);
    b->right = bst_free(b->right);
    printf("free %s\n", b->key);
    free(b->key);
    free(b);
    return b;
}


bst bst_delete(bst b, char *str){
    int search = bst_search(b, str);
    bst temp;
    char *t;
    if (search == 0){
        
        return b;
    }else if (strcmp(b->key, str) == 0){

        /* Splicing out the node*/
        if ((b->left == NULL) && (b->right == NULL)){
            printf("free %s\n", b->key);
            free(b->key);
            free(b);
            b = NULL;
        }else if((b->left != NULL) ^ (b->right != NULL)){
            printf("%s has one leaf\n", b->key);
            temp = b;
            if (b->left != NULL){
                b = b->left;
            }else{
                b = b->right;
            }
            printf("free %s\n", b->key);
            free(temp->key);
            free(temp);
        }else{
            printf("%s has 2 leaves\n", b->key);
            /* temp is the root node, b is the successor*/
            temp = b;
            temp = find_successor(temp);
            printf("sucessor of %s is %s\n", b->key, temp->key);
            t = b->key;
            b->key = temp->key;
            temp->key = t;

            printf("temp is now %s\n", b->key);
            b->right = bst_delete(b->right, temp->key);
            return b;
        }
        return b;
        
    }else if (strcmp(b->key, str) > 0){
        printf("search left node\n");
        b->left = bst_delete(b->left, str);
    }else{
        printf("search right node\n");
        b->right = bst_delete(b->right, str);
    }
    return b;
}

void bst_inorder(bst b, void f(char *str)){
    if (b == NULL){
        return;
    } 
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);
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

bst bst_new(){
    return NULL;
}

void bst_preorder(bst b, void f(char *str)){
    if (b == NULL){
        return;
    }
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
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
