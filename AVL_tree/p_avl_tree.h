#ifndef _P_AVL_TREE_H_
#define _P_AVL_TREE_H_

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "p_queue.h"

#define GO_LEFT (1)
#define GO_RIGHT (2)

#define BALANCED (1)
#define NOT_BALANCED (2)

#define LEFT_CHILD (1)
#define RIGHT_CHILD (2)

#define DO_DEBUG

#ifdef DO_DEBUG
#define DEBUG_PRINT(...) printf("[TREE]"  __VA_ARGS__);
#else
#define DEBUG_PRINT(...) ;
#endif

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

typedef void (*rotate_s)(avl_node* node);


avl_tree* AVLTree_createTree(void);
void AVLTree_destroyTree(avl_tree* Tree);

void AVLTree_insertNode(avl_tree* Tree, void* new_node, int (*compare)(void*a, void*b));
void AVLTree_deleteNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));
void AVLTree_searchNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));

void AVLTree_display(avl_tree* tree, void (*print_node)(void*));

#endif // _P_AVL_TREE_H_
