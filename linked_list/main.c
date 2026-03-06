#include<stdio.h>
#include<stdlib.h>

typedef struct node_t{
    int data;
    struct node_t* next;
}node;

void main(){

    printf("In this example linked list is created\n");

    node* ll_head = (node*) malloc(sizeof(node)); 
    ll_head->data = 0;

    for(int i=1; i<10; i++){
       node* new_node = (node*) malloc(sizeof(node));
        new_node->next = ll_head;
        new_node->data = 10*i;
        ll_head = new_node;
    }

    printf("\n printing the linked list\n");
    while(ll_head){
        printf("%d\n", ll_head->data);
    
        ll_head = ll_head->next;
    }
    return;
}