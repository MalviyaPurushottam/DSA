#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <fcntl.h>

#include "queue.h"

#define GO_LEFT (1)
#define GO_RIGHT (2)

#define BALANCED (1)
#define NOT_BALANCED (2)

typedef struct avl_node_t{
    void* nptr;
    int height;
    struct avl_node_t* parent;
    struct avl_node_t* right;
    struct avl_node_t* left;
} avl_node;

typedef struct{
    avl_node* root;
} avl_tree;

typedef avl_node* (*rotate_s)(avl_node* node);


avl_tree* AVLTree_createTree(void);
void AVLTree_destroyTree(avl_tree* Tree);

void AVLTree_insertNode(avl_tree* Tree, void* new_node, int (*compare)(void*a, void*b));
void AVLTree_deleteNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));
void AVLTree_searchNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));

void AVLTree_display(avl_tree* tree, void (*print_node)(void*));



#endif // AVL_TREE_H
