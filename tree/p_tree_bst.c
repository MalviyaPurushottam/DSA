#include "p_tree_bst.h"
#include "p_queue.h"
#include <stdio.h>

tree_bst* BST_create(void){
    tree_bst* tree = (tree_bst*)malloc(sizeof(tree_bst));
    tree->root = NULL;

    return tree;

}

tree_bst* BST_insert(tree_bst* Tree, void* new_node, int (*comp_func)(void* , void*)){
    // get handle to a node 
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    node->data_ptr = new_node;
    node->parent = NULL;
    node->left_child = NULL;
    node->right_child = NULL;

    // if the tree is empty then assign this node as root node
    if(Tree->root == NULL){
        Tree->root = node;
        return Tree;
    }
    // other wise we are going to do BST search
    tree_node* temp = Tree->root;
    while(1){
        if(comp_func(temp->data_ptr, node->data_ptr)){
            if(temp->left_child != NULL){
                temp = temp->left_child;
            }  
            else{
                printf("inserting node in left child ...\n");
                temp->left_child = node;
                node->parent = temp;
                return Tree;
            }
        }
        else {
            if(temp->right_child != NULL){
                temp = temp->right_child;
            }
            else {
                printf("inserting node in right child ...\n");
                temp->right_child = node;
                node->parent = temp;
                return Tree;
            }
        }
    }
}
tree_bst* BST_delete(tree_bst* Tree, void* new_node);

tree_node* BST_successor(tree_bst* Tree, tree_node* node);
tree_node* BST_predecessor(tree_bst* Tree, tree_node* node);

void print_tree(tree_bst* tree, void (*print_node)(void* )){

    printf("Here the tree is being printed by in level traversal ... \n");

    queue* Q = Q_create();
    if(tree->root != NULL){
        Q_enqueue(Q, tree->root);
        while(Q_isEmpty(Q)){
            int size = Q_size(Q);
            for(int i = 0; i<size; i++){
                // dequeue node
                tree_node* node = Q_dequeue(Q);
                // print info
                print_node(node->data_ptr);
                // enqueue children
                if(node->left_child != NULL){
                    Q_enqueue(Q, node->left_child);
                }
                if(node->right_child != NULL){
                    Q_enqueue(Q, node->right_child);
                }
            }
           printf("\n");
        }
    }
    return;
}