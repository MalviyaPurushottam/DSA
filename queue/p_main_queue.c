#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "p_queue.h"


int main(){

    printf("This is program to understand queue...\n");
    printf("Creating queue...\n");
    Queue* queue = Queue_create();

    for(int i = 1; i<30; i+= 2){
        queue = EnQueue(queue, i);
    }

    Queue_print(queue);
    
    printf("Removing an element at a time and printing it with length...\n");
    while (Queue_isEmpty(queue) != true) {
        printf("Length of queue is %d. \n", Queue_size(queue));
        Queue_print(queue);
        queue = DeQueue(queue);
    }

    return 0;
}