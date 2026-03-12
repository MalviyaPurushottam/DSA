#include "p_stack.h"
#include <stdio.h>
#include <stdlib.h>


stack_node* Stack_create(int new_data){
    stack_node* stack_top = (stack_node*) malloc(sizeof(stack_node));
    stack_top->data = new_data;
    stack_top->below_node = NULL;

    return stack_top;
}

stack_node* Stack_push(stack_node* top, int new_data){

    stack_node* new_node = (stack_node*)malloc(sizeof(stack_node));
    new_node->below_node = top;
    new_node->data = new_data;
    top = new_node;
    return top;

}

stack_node* Stack_pop(stack_node* top){

   // printf("Removing an element %d.\n", top->data);
    stack_node* temp = top;
    top = top->below_node;
    free(temp);
    return top;

}

int Stack_no_of_elements(stack_node* top){
    stack_node* temp = top;
    int count = 0;
    while(temp != NULL){
        temp = temp->below_node;
        count++;
    }
    return count;
}

void Stack_print(stack_node* top){

    stack_node* temp = top;
    printf("Now printing the stack\n");
    while(temp){
        printf("%d -> ", temp->data);
        temp = temp->below_node;
    }
    printf("NULL\n");
    return;
}
