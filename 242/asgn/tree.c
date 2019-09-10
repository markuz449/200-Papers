#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } tree_colour;

/**
 * The struct for a treenode.
 *
 * Contents:
 *     @li key the string item.
 *     @li colour enum type that is either RED or BLACK.
 *     @li left is the left tree struct.
 *     @li right is the right tree struct.
 *     @li tree_type enum type is either a RBT or BST.
 *     @li frequency the number of duplicate items.
 */
struct treenode{
    char *key;
    tree_colour colour;
    tree left;
    tree right;
    tree_t tree_type;
    int frequency;
};

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
    if(t->key != NULL) {
        fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
                t->key, t->key, t->frequency,
                (RBT == t->tree_type && RED == t->colour) ? "red":"black");
    }
    if(t->left != NULL) {
        tree_output_dot_aux(t->left, out);
        fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
    }
    if(t->right != NULL) {
        tree_output_dot_aux(t->right, out);
        fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
    }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
    fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
    tree_output_dot_aux(t, out);
    fprintf(out, "}\n");
}

/**
 * Sets the root node to Black to balance the RBT.
 *
 * @param t the tree to have root node fixed.
 *
 * @return t the fixed RBT with the correct coloured root node.
 */
tree tree_fix_root(tree t){
    t->colour = BLACK;
    return t;
}

/**
 * Rotates the tree right, balancing the tree or
 * changing the case so it can become balanced.
 *
 * @param t the tree that is unbalanced.
 *
 * @return t the corrected tree.
 */
static tree right_rotate(tree t){
    tree temp = t;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    return t;
}


/**
 * Rotates the tree left, balancing the tree or
 * changing the case so it can become balanced.
 *
 * @param t the tree that is unbalanced.
 *
 * @return t the corrected tree.
 */
static tree left_rotate(tree t){
    tree temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    return t;
}


/**
 * Fixes the RBT and makes sure that it is balanced and the
 * black height is equal. The fuction checks if there is consecutive
 * red nodes in the tree. Then depending on if the node on the opposite
 * side is RED different actions are taken.
 * If the opposite node is RED, recolour the tree.
 * If the opposite node is BLACK, rotate the tree and recolour.
 *
 * @param r a RBT that could need fixing.
 *
 * @return r a completely balanced RBT.
 */
static tree tree_fix(tree r){
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


/**
 * Free's all of the trees allocated memory and
 * frees the components of the tree as well.
 * 
 * @param t the tree to be freed.
 *
 * @return NULL the null tree is returned. 
 */
tree tree_free(tree t){
    if (t == NULL){
        return t;
    }
    t->left = tree_free(t->left);
    t->right = tree_free(t->right);
    free(t->key);
    free(t);
    return NULL;
}

/**
 * Inserts a new string into the tree and sets all of the
 * struct components values. The function makes sure that
 * where the string is inserted is in the correct place in the tree.
 * Calls the tree_fix method if the tree is a RBT.
 *
 * @param t the tree that is going to have a string inserted.
 * @param str the string that is going to be inserted into the tree.
 * @param tt int value  which tells the function if the tree is a RBT or BST.
 *
 * @return t the new tree with the inserted string.
 */
tree tree_insert(tree t, char *str, int tt){
    if (t == NULL){
        t = emalloc(5 * sizeof(t));
        t->key = (char*)emalloc((strlen(str) + 1) * sizeof(char*));
        strcpy(t->key, str);
        t->colour = RED;
        t->left = tree_new();
        t->right = tree_new();
        t->tree_type = tt;
        t->frequency = 1;
    } else {
        if (strcmp(t->key, str) == 0){
            t->frequency++;
            return t;
        } else if (strcmp(t->key, str) > 0){
            t->left = tree_insert(t->left, str, tt);
        } else {
            t->right = tree_insert(t->right, str, tt);
        }
    }
    if(t->tree_type == 1){
        t = tree_fix(t);
    }
    return t;
}

/**
 * Creates a NULL tree.
 *
 * @return NULL a new tree object that is set to NULL.
 */
tree tree_new(){
    return NULL;
}

/**
 * Prints the contents of the tree in order of the contents.
 *
 * @param t the tree whose contents is to be printed.
 * @param f the function of how the contents is to be printed.
 */
void tree_inorder(tree t, void f(int freq, char *word)){
    if (t == NULL){
        return;
    } 
    tree_inorder(t->left, f);
    f(t->frequency, t->key);
    tree_inorder(t->right, f);
}

/**
 * Prints the contents of the tree in order that the nodes appear in the tree.
 *
 * @param t the tree whose contents is to be printed.
 * @param f the function of how the contents is to be printed.
 */
void tree_preorder(tree t, void f(int freq, char *word)){
    if (t == NULL){
        return;
    }
    f(t->frequency, t->key);
    tree_preorder(t->left, f);
    tree_preorder(t->right, f);
}

/**
 * Seraches the tree recursively and checks if a particular string
 * is in the tree. 0 is returned if the String is not found and 1
 * if the string is found.
 *
 * @param t the tree that is going to be searched.
 * @param str the string that is being checked if it is in the tree.
 *
 * @return 0 if the str was not found in the tree.
 * @return 1 if the str was found in the tree.
 * @return tree_seach(t->left, str) searches the left if the str
 was not found but the tree is not NULL.
 * @return tree_seach(t->right, str) searches the right if the str
 was not found but the tree is not NULL.   
*/
int tree_search(tree t, char *str){
    if (t == NULL){
        return 0;
    } else if(strcmp(t->key, str) == 0){
        return 1;
    } else if(strcmp(t->key, str) > 0){
        return tree_search(t->left, str);
    } else{
        return tree_search(t->right, str);
    }
}
