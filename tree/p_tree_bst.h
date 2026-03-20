#ifndef _P_TREE_BST_H_
#define _P_TREE_BST_H_

#include <stdlib.h>
#include <stdio.h>

#include "p_queue.h"


typedef struct treenode_t{
    void* data_ptr;
    struct treenode_t* parent;
    struct treenode_t* left_child;
    struct treenode_t* right_child;
} tree_node;

typedef struct {
    tree_node* root;
} tree_bst;

tree_bst* BST_create(void);

tree_bst* BST_insert(tree_bst* Tree, void* new_node, int (*comp_func)(void* , void*));
tree_bst* BST_delete(tree_bst* Tree, void* node);

tree_node* BST_successor(tree_bst* Tree, tree_node* node);
tree_node* BST_predecessor(tree_bst* Tree, tree_node* node);

void print_tree(tree_bst* tree, void (*print_node)(void*));





#endif  // _P_TREE_BST_H_