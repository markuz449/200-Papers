#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } rbt_colour;

struct rbtnode {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

rbt rbt_fix_root(rbt r){
    r->colour = BLACK;
    return r;
}

static rbt right_rotate(rbt r){
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

static rbt left_rotate(rbt r){
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

static rbt rbt_fix(rbt r){
    if((r->left == NULL) && (r->right == NULL)){
        return r;
    }
    if (r->left != NULL && IS_RED(r->left)){
        if (r->left->left != NULL && IS_RED(r->left->left)){
            if (IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else{
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        } if (r->left->right != NULL && IS_RED(r->left->right)){
            if (IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        }
    }
    if (r->right != NULL && IS_RED(r->right)){
        if (r->right->left != NULL && IS_RED(r->right->left)){
            if (IS_RED(r->left)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        } if (r->right->right != NULL && IS_RED(r->right->right)){
            if (IS_RED(r->left)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        }
    } 
    return r;
}

static rbt find_successor(rbt r){
    r = r->right;
    while(r->left != NULL){
        r = r->left;
    }
    return r;
}


rbt rbt_free(rbt r){
    if (r == NULL){
        return r;
    }
    r->left = rbt_free(r->left);
    r->right = rbt_free(r->right);
    free(r->key);
    free(r);
    return NULL;
}


rbt rbt_delete(rbt r, char *str){
    int search = rbt_search(r, str);
    rbt temp;
    char *t;
    if (search == 0){
        return r;
    }else if (strcmp(r->key, str) == 0){

        /* Splicing out the node*/
        if ((r->left == NULL) && (r->right == NULL)){
            free(r->key);
            free(r);
            r = NULL;
        }else if((r->left != NULL) ^ (r->right != NULL)){
            temp = r;
            if (r->left != NULL){
                r = r->left;
            }else{
                r = r->right;
            }
            free(temp->key);
            free(temp);
        }else{
            /* temp is the root node, r is the successor*/
            temp = r;
            temp = find_successor(temp);
            t = r->key;
            r->key = temp->key;
            temp->key = t;

            r->right = rbt_delete(r->right, temp->key);
            return r;
        }
        return r;
        
    }else if (strcmp(r->key, str) > 0){
        r->left = rbt_delete(r->left, str);
    }else{
        r->right = rbt_delete(r->right, str);
    }
    return r;
}

void rbt_inorder(rbt r, void f(char *str)){
    if (r == NULL){
        return;
    } 
    rbt_inorder(r->left, f);
    f(r->key);
    rbt_inorder(r->right, f);
}

rbt rbt_insert(rbt r, char *str){
    if (r == NULL){
        r = emalloc(4 * sizeof(r));
        r->key = (char*)emalloc((strlen(str) + 1) * sizeof(char*));
        strcpy(r->key, str);
        r->colour = RED;
        r->left = rbt_new();
        r->right = rbt_new();
        printf("inserted %s\n", r->key);
        /*r = rbt_fix(r);*/
        return r;
    } else {
        if (strcmp(r->key, str) == 0){
            return r;
        } else if (strcmp(r->key, str) > 0){
            r->left = rbt_insert(r->left, str);
        } else {
            r->right = rbt_insert(r->right, str);
        }
        r = rbt_fix(r);
        return r;
    }
}

rbt rbt_new(){
    return NULL;
}

void rbt_preorder(rbt r, void f(char *str)){
    if (r == NULL){
        return;
    }
   
    if (r->colour == 0){
        printf("Red :   ");
    } else {
        printf("Black : ");
    }
    f(r->key);
    printf("\n");
    rbt_preorder(r->left, f);
    rbt_preorder(r->right, f);    
}

int rbt_search(rbt r, char *str){
    if (r == NULL){
        return 0;
    }else if(strcmp(r->key, str) == 0){
        return 1;
        /* return < 0 if r->key < str*/
    }else if(strcmp(r->key, str) > 0){
        return rbt_search(r->left, str);
    }else{
        return rbt_search(r->right, str);
    }
}



