#ifndef _P_STACK_H_
#define _P_STACK_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct stacknode_t{
    int data;
    struct stacknode_t* below_node;
} stack_node;

stack_node* Stack_create(int new_data);
stack_node* Stack_push(stack_node* top, int new_data);
stack_node* Stack_pop(stack_node* top);
int Stack_no_of_elements(stack_node* top);
void Stack_print(stack_node* top);




#endif  // _P_STACK_H_