#include<stdio.h>
#include<stdlib.h>

typedef struct node_t{
    int data;
    struct node_t* next;
}node;

node* remove_element(node* head, int key){
    node* alias = head;
    // base case
    if(alias->data == key){
        head = head->next;
        return head;
    }

    while(alias){
        if(alias->next == NULL){
            alias = alias->next;
            break;
        }

        if(alias->next->data == key){
            break;
        }

        alias = alias->next;
    }

    if(alias == NULL){
        return head;
    }

    node* temp = (node*)malloc(sizeof(node));
    temp = alias->next->next;
    free(alias->next);
    alias->next = temp;

    return head;

}


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

    // remove the element with key 60
    ll_head = remove_element(ll_head, 0);

    printf("\n printing the linked list\n");
    while(ll_head){
        printf("%d\n", ll_head->data);
    
        ll_head = ll_head->next;
    }
    return;
}