#include "p_avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

static void avl_r_left_left(avl_node* node);
static void avl_r_left_right(avl_node* node);
static void avl_r_right_left(avl_node* node);
static void avl_r_right_right(avl_node* node);

static int balance_and_update_height(avl_node* node);

rotate_s AVL_rotate[2][2] = {
    avl_r_left_left,
    avl_r_left_right,
    avl_r_right_left,
    avl_r_right_right,
};

avl_tree* AVLTree_createTree(void){
    avl_tree* T = (avl_tree*)malloc(sizeof(avl_tree));

    T->root = NULL;

    return T;
}
void AVLTree_destroyTree(avl_tree* Tree);

void AVLTree_insertNode(avl_tree* Tree, void* new_node, int (*compare)(void*a, void*b)){
    // insert the node in the right place 
    // create a new node 
    avl_node* node = (avl_node*)malloc(sizeof(avl_node));
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->nptr = new_node;

    // get the location and update the linkages
    // edge case if this is the first node
    if(Tree->root == NULL){
        Tree->root = node;
        return;
    }

    // if the node is data is less GO_LEFT other wise right
    avl_node* temp = Tree->root;
    while (temp != NULL) {
        if(GO_LEFT == compare(node->nptr, temp->nptr)){
            // going left if no where to go then node will go there
            if (temp->left == NULL) {
                temp->left = node;
                node->parent = temp;
                break; // breaking fro updating the height otherwise would have returned
            }
            else {
                temp = temp->left;
            }
        }
        else{
            // going right if no where to go then node will go there
            if (temp->right == NULL) {
                temp->right = node;
                node->parent = temp;
                break; // breaking fro updating the height otherwise would have returned
            }
            else {
                temp = temp->right;
            }
        }
    }

    // update the height and look out for the rotation 
    // will always be starting from the lat second level
    while (temp!= NULL) {
        // try looking for imbalance and then update height coz while balancing there no need to update
        if(balance_and_update_height(temp) == BALANCED){
            // update for next loop
            temp = temp->parent;
            continue;
        }
        else {
            // as in AVL tree for insertion the first rotation all you need and height is same as the old one
            break;  
        }
    }
    return;

}
void AVLTree_deleteNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));
void AVLTree_searchNode(avl_tree* Tree, void* old_node, int (*compare)(void*a, void*b));

void AVLTree_display(avl_tree* tree, void (*print_node)(void*));

static int balance_and_update_height(avl_node* node){
    int left_height = 0, right_height = 0;
    if(node->left != NULL){
        left_height = node->left->height;
    }
    if(node->right != NULL){
        right_height = node->right->height;
    }

    int diff = left_height-right_height;
    if(diff == 0){
        return BALANCED;
    }
    else if((-1 == diff) || (diff == 1)){
        node->height += 1;
        return BALANCED;
    }
    else{
        // now rotate the tree
        int i = 0, j = 0;
        // get the bigger tree 4 cases
        //  NEED TO FUCKING OPTIMISE THIS WITH SOMETHING BETTER VERY MUCH LESS JUMP STATEMENT IN CPP
        if(diff>0){
            if(node->left->left == NULL){
                j = 1;
            }
            else if(node->left->right == NULL) {
                j = 0;
            }
            else{
                if(node->left->left->height < node->left->right->height){
                    j = 1;
                }
            }
        }
        else {
            i = 1;
            if (node->right->left == NULL) {
                j = 1;
            }
            else if (node->right->right == NULL) {
                j = 0;
            }
            else {
                if (node->right->left->height < node->right->right->height) {
                    j = 1;
                }
            }
        }
        AVL_rotate[i][j](node);
        return NOT_BALANCED;
    }
}

// NOW comes the rotation
static void avl_r_left_left(avl_node* node){
    /*
              z                            y                            
             / \                         /   \                         
            y  t4                       x     z                         
           / \                         / \   / \                       
          x  t3                       t1 t2 t3 t4                         
         / \                                                    
        t1 t2                                                    
    */
    avl_node* z = node;
    avl_node* y = z->left;
    avl_node* x = y->left;
    // 2 case depending on parent of z
    if(z->parent != NULL){
        y->parent = z->parent;
        // now child
        if(y->parent->left == y){
            y->parent->left = y;
        }
        else {
            y->parent->right = y;
        }
    }

    // making t3 child of z
    z->left = y->right;
    z->left->parent = z;

    // making x and z child of y
    y->left = x;
    x->parent = y;

    y->right = z;
    z->parent = y;

    // final transform
    node = y;
    return;
}

static void avl_r_left_right(avl_node* node){
    /*
              z                            x                            
             / \                         /   \                         
            y  t4                       y     z                         
           / \                         / \   / \                       
          t1  x                        t1 t2 t3 t4                         
             / \                                                    
            t2 t3                    
    */
    avl_node* z = node;
    avl_node* y = z->left;
    avl_node* x = y->right;
    // 2 case depending on parent of z
    if(z->parent != NULL){
        x->parent = z->parent;
        // now child
        if(x->parent->left == x){
            x->parent->left = x;
        }
        else {
            x->parent->right = x;
        }
    }

    // making t3 child of z
    z->left = x->right;
    z->left->parent = z;
    // making t2 child of y
    y->right = x->left;
    y->right->parent = y;

    // making y and z child of x
    x->left = y;
    y->parent = x;

    x->right = z;
    z->parent = x;
    
    // final transform
    node = x;
    return;
}

static void avl_r_right_left(avl_node* node){
    /*
              z                            x                            
             / \                         /   \                         
            t1  y                       z     y                         
               / \                     / \   / \                       
              x  t4                   t1 t2 t3 t4                         
             / \                                                    
            t2 t3                    
    */
    avl_node* z = node;
    avl_node* y = z->right;
    avl_node* x = y->left;
    // 2 case depending on parent of z
    if(z->parent != NULL){
        x->parent = z->parent;
        // now child
        if(x->parent->left == x){
            x->parent->left = x;
        }
        else {
            x->parent->right = x;
        }
    }

    // making t3 child of y
    y->left = x->right;
    y->left->parent = y;
    // making t2 child of x
    z->right = x->left;
    z->right->parent = z;

    // making y and z child of x
    x->right = y;
    y->parent = x;

    x->left = z;
    z->parent = x;
    
    // final transform
    node = x;
    return;
}

static void avl_r_right_right(avl_node* node){
    /*
              z                            y                            
             / \                         /   \                         
            t1  y                       z     x                         
               / \                     / \   / \                       
              t2  x                   t1 t2 t3 t4                         
                 / \                                                    
                t3 t4                    
    */
    avl_node* z = node;
    avl_node* y = z->right;
    avl_node* x = y->right;
    // 2 case depending on parent of z
    if(z->parent != NULL){
        y->parent = z->parent;
        // now child
        if(y->parent->left == y){
            y->parent->left = y;
        }
        else {
            y->parent->right = y;
        }
    }

    // making t2 child of z
    z->right = y->left;
    z->right->parent = z;

    // making x and z child of y
    y->right = x;
    x->parent = y;

    y->left = z;
    z->parent = y;

    // final transform
    node = y;
    return;
}