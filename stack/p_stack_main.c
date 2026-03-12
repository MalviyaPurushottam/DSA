#include <stdio.h>
#include <stdlib.h>
#include "p_stack.h"


int main(){

    printf("This is program to understand stack...\n");
    printf("Creating stack...\n");
    stack_node* Stack_top = NULL;

    Stack_top = Stack_create(0);
    for(int i = 1; i<20; i+= 2){
        Stack_top = Stack_push(Stack_top, i);
    }

    Stack_print(Stack_top);
    
    printf("Removing an element at a time and printing it with length...\n");
    while (Stack_top != NULL) {
        printf("Height of stack is %d. \n", Stack_no_of_elements(Stack_top));
        Stack_print(Stack_top);
        Stack_top = Stack_pop(Stack_top);
    }

    return 0;
}