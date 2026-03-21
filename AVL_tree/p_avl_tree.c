#include "p_avl_tree.h"
#include <stdio.h>
#include <stdlib.h>


rotate_s rotate_node[2][2] = {
    avl_r_left_left,
    avl_r_left_right,
    avl_r_right_left,
    avl_r_right_right
};


avl_tree* AVLTree_createTree(void){
    avl_tree* tree = (avl_tree*)malloc(sizeof(avl_tree));
    tree->root = NULL;

    return tree;
}
void AVLTree_destroyTree(avl_tree* Tree){
    if(Tree->root == NULL){
        free(Tree);
        return;
    }
    // if tree is not empty go to each and every node and free it
    // to be done ...
}

void AVLTree_insertNode(avl_tree* Tree, void* new_node, int (*compare)(void*a, void*b)){
    // get memory for the node
    avl_node* node = (avl_node*)malloc(sizeof(avl_node));
    
    // init the node with zero
    node->nptr = new_node;
    node->height = 1;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    // find the loaction for the node and update the node
    if(Tree->root == NULL){
        Tree->root = node;
        return;
    }
    else {
        avl_node* temp_root = Tree->root;
        while(temp_root != NULL){
            int result = compare(temp_root->nptr, node->nptr);
            if(result == GO_LEFT){
                if(temp_root->left == NULL){
                    temp_root->left = node;
                    node->parent = temp_root;
                    break;
                }
                else {
                    temp_root = temp_root->left;
                }
            }
            else if (result == GO_RIGHT) {
                if(temp_root->right == NULL){
                    temp_root->right = node;
                    node->parent = temp_root;
                    break;
                }
                else {
                    temp_root = temp_root->right;
                }
            }
        }
    }
    // update the height of the tree and if imbalance then do rotation

    avl_node *temp_node = node->parent;
    while (1) {
        // check for imbalance
        int is_imbalance = find_imbalance(temp_node);
        if(is_imbalance == NOT_BALANCED){
            balance(temp_node);
            return;
        }
        else if(is_imbalance == BALANCED){
            update_height(temp_node);
            temp_node = temp_node->parent;
            if(temp_node == NULL){
                return;
            }
            continue;
        }
    }

}
void AVLTree_deleteNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));
void AVLTree_searchNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));

void AVLTree_display(avl_tree* tree, void (*print_node)(void*)){

    printf("Here the tree is being printed by in level traversal ... \n");

    queue* Q = Q_create();
    if(tree->root != NULL){
        Q_enqueue(Q, tree->root);
        while(Q_isEmpty(Q)){
            int size = Q_size(Q);
            for(int i = 0; i<size; i++){
                // dequeue node
                avl_node* node = Q_dequeue(Q);
                // print info
                print_node(node->nptr);
                // enqueue children
                if(node->left != NULL){
                    Q_enqueue(Q, node->left);
                }
                if(node->right != NULL){
                    Q_enqueue(Q, node->right);
                }
            }
          // printf("\n");
        }
    }
    return;
}

static int find_imbalance(avl_node* node){
    if(node->left == NULL){
        if(node->right->height > 1){
            return NOT_BALANCED;
        }
    }
    else if (node->right == NULL) {
        if(node->left->height > 1){
            return NOT_BALANCED;
        }
    }
    else {
        unsigned int diff = node->left->height - node->right->height;
        if((diff <= -2) || (diff >= 2)){
            return NOT_BALANCED;
        }
    }
    return BALANCED;
}

static void update_height(avl_node* node){
    if(node->left == NULL){
        node->height = (node->right->height + 1);
    }
    else if (node->right == NULL) {
        node->height = (node->left->height + 1);
    }
    else {
        if(node->right->height >= node->left->height){
            node->height = (node->right->height + 1);
        }
        else{
            node->height = (node->left->height + 1);
        }
    }
    return ;
}

static void balance(avl_node* node){
    DEBUG_PRINT("Balance called ... \n");
    // there are 4 types of rotation
    if(go_left(node) == GO_LEFT){
        rotate_node[0][(go_left(node->left))-1](node);
    }
    else{
        rotate_node[1][(go_left(node->right))-1](node);
    }
    return;
}

static int go_left(avl_node* node){
    
    if(node->right == NULL){
        return GO_LEFT;
    }
    if(node->left == NULL){
        return GO_RIGHT;
    }
    if (node->left->height >= node->right->height) {
        return GO_LEFT;
    }
    return GO_RIGHT;
}

static void avl_r_left_left(avl_node* node){
    /*
                z : node                           y : node                                                           
               / \                                / \                         
              y  t4                              x    z                        
             / \                                / \   / \                      
            x  t3                              t1 t2 t3 t4                            
           / \                                                          
          t1  t2                                                                    
    */

    avl_node* z = node;
    avl_node* y = node->left;
    avl_node* x = node->left->left;

    // find if parent is present or not
    if(node->parent != NULL){
        // get which child node is
        if(node->parent->right == node){
            y->parent = node->parent;
            y->parent->right = y;
            
        }
        else if(node->parent->left == node){
            y->parent = node->parent;
            y->parent->left = y;
        }
    }

    // make t3 child of z freeing y
    z->left = y->right;
    y->right->parent = z;

    // make x and z child of y
    y->right = z;
    z->parent = y;

    y->left = x;
    x->parent = z;

    // make node as y
    node = y;
    node->left->height = node->height - 1;
    node->right->height = node->height - 1;

    return;
}

static void avl_r_left_right(avl_node* node){
    /*
                z : node                 x : node
               / \                     /   \
              y  t4                   y     z
             / \                     / \   / \ 
            t1  x                   t1 t2 t3 t4 
               / \               
              t2  t3                 
    */
    avl_node* z = node;
    avl_node* y = node->left;
    avl_node* x = node->left->right;

    // find if parent is present or not
    if(node->parent != NULL){
        // get which child node is
        if(node->parent->right == node){
            x->parent = node->parent;
            x->parent->right = x;
            
        }
        else if(node->parent->left == node){
            x->parent = node->parent;
            x->parent->left = x;
        }
    }
    
    // make t3 child of z freeing x
    z->left = x->right;
    x->right->parent = z;

    // make t2 child of y freeing x
    y->right = x->left;
    x->left->parent = y;

    // make y and z child of x
    x->right = z;
    z->parent = x;

    x->left = y;
    y->parent = x;

    // make node as x
    node = x;
    node->left->height = node->height - 1;
    node->right->height = node->height - 1;

    return;
}

static void avl_r_right_left(avl_node* node){
    /*
                z : node                 x : node
               / \                     /   \
             t1   y                   z     y
                 / \                 / \   / \ 
                x   t4               t1 t2 t3 t4 
               / \               
              t2  t3                 
    */
    avl_node* z = node;
    avl_node* y = node->right;
    avl_node* x = node->right->left;

    // find if parent is present or not
    if(node->parent != NULL){
        // get which child node is
        if(node->parent->right == node){
            x->parent = node->parent;
            x->parent->right = x;
            
        }
        else if(node->parent->left == node){
            x->parent = node->parent;
            x->parent->left = x;
        }
    }
    
    // make t3 child of y freeing x
    y->left = x->right;
    x->right->parent = y;

    // make t2 child of z freeing x
    z->right = x->left;
    x->left->parent = z;

    // make y and z child of x
    x->right = z;
    z->parent = x;

    x->left = y;
    y->parent = x;

    // make node as x
    node = x;
    node->left->height = node->height - 1;
    node->right->height = node->height - 1;

    return;
}

static void avl_r_right_right(avl_node* node){    
    /*
                z : node                    y : node
               / \                        /   \     
              t1  y                      z     x
                / \                     / \   / \  
               t2  x                   t1 t2 t3 t4
                  / \
                 t3  t4        
    */

    avl_node* z = node;
    avl_node* y = node->right;
    avl_node* x = node->right->right;

    // find if parent is present or not
    if(node->parent != NULL){
        // get which child node is
        if(node->parent->right == node){
            y->parent = node->parent;
            y->parent->right = y;
            
        }
        else if(node->parent->left == node){
            y->parent = node->parent;
            y->parent->left = y;
        }
    }
    
    // make t2 child of z freeing y
    z->right = y->left;
    y->left->parent = z;

    // make x and z child of y
    y->left = z;
    z->parent = y;

    y->right = x;
    x->parent = z;

    // make node as y
    node = y;
    node->left->height = node->height - 1;
    node->right->height = node->height - 1;
    return;
}