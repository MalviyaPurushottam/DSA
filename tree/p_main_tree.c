#include <stdio.h>
#include <stdlib.h>
#include "p_tree_bst.h"

typedef struct{
    int data;
}node_t;

int comp_node(void* a, void* b);
void display_node(void* a);

int main(){

    printf("This is program to understand tree");
    tree_bst* T = BST_create();

    printf("Inserting nodes ... \n");
    for(int i = 0; i< 10; i++){
        node_t* node = (node_t*)malloc(sizeof(node_t));

        node->data = i*2;
        printf("Inserting %d ...\n", node->data);
        T = BST_insert(T, node, comp_node);
    }
    for(int i = 1; i<= 10; i++){
        node_t* node = (node_t*)malloc(sizeof(node_t));

        node->data = i*2-1;
        printf("Inserting %d ...\n", node->data);
        T = BST_insert(T, node, comp_node);
    }   

    print_tree(T, display_node);

    return 0;
}

int comp_node(void* a, void* b){
    node_t* A = (node_t*)a;
    node_t* B = (node_t*)b;

    if(A->data <= B->data){
        return 0;
    }
    else{
        return 1;
    }
}

void display_node(void* a){
    node_t* temp = (node_t*) a;
    printf("%d\t", temp->data);
    return;
}
