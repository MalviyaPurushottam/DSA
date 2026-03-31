#include <stdio.h>

#include "queue.h"
#include "avl_tree.h"

typedef struct {
    int data;
}dnode_t;

int node_comp(void* a, void*b);
void node_disp(void* a);

void queue_implement(void);
int main()
{
    // Queue implementation
    queue_implement();

    // AVL tree implementation
    printf("This is the program to understand the implementation of AVL tree rotation and all!\n");
    avl_tree* T = AVLTree_createTree();
    for (int var = 0; var < 10; ++var) {
        dnode_t* n = (dnode_t *) malloc(sizeof(dnode_t));
        n->data = 2*var;
        AVLTree_insertNode(T, n, node_comp);
        AVLTree_display(T, node_disp);
    }
    for (int var = 0; var < 10; ++var) {
        dnode_t* n = (dnode_t *) malloc(sizeof(dnode_t));
        n->data = 2*var+1;
        AVLTree_insertNode(T, n, node_comp);
        AVLTree_display(T, node_disp);
    }
    AVLTree_display(T, node_disp);
    return 0;
}

int node_comp(void* a, void*b){
    dnode_t *ta = (dnode_t*)a;
    dnode_t *tb = (dnode_t*)b;
    if(ta->data<=tb->data){
        return GO_LEFT;
    }
    else{
        return GO_RIGHT;
    }
}
void node_disp(void* a){
    dnode_t *ta = (dnode_t*)a;
    printf("%d\t", ta->data);
return ;
}

void queue_implement(void){
    printf("this part will implement queue\n");
    queue* q = Q_create();
    for(int i = 0; i < 10; i++){
        int * iptr = (int*)malloc(sizeof(int));
        *iptr = 2*i+1;
        Q_enqueue(q, iptr);
    }
    int *i;
    while (Q_isEmpty(q)) {
        i = (int*)Q_dequeue(q);
        printf("element removed is %d, current size is %d\n", *i, Q_size(q));
    }
    return;
}