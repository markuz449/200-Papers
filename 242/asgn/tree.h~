#ifndef TREE_H_
#define TREE_H_

typedef enum tree_e { BST, RBT } tree_t;

typedef struct treenode *tree;

extern tree tree_free(tree t);
extern void tree_inorder(tree t, void f(int freq, char *word));
extern tree tree_insert(tree t, char *str, int tt);
extern tree tree_new();
extern void tree_preorder(tree t, void f(int freq, char *word));
extern int tree_search(tree t, char *str);
extern void tree_output_dot(tree t, FILE *out);
extern tree tree_fix_root(tree t);

#endif
