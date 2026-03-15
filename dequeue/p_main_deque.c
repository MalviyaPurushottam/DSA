#include <stdio.h>
#include "p_deque.h"

int main(){
    printf("This is program to understand deque...\n");
    printf("Creating deque...\n");
    Deque* d = Deque_create();
    node temp;
    for(int i = 1; i<30; i+= 2){
        temp.data = i;
        d = Deque_insertFirst(d, &temp);
        temp.data = i-1;
        d = Deque_insertLast(d, &temp);
    }

    Deque_printFromStart(d);
    Deque_printFromLast(d);
    
    printf("Removing an element at a time and printing it with length...\n");
    while (Deque_size(d) != 0) {
        printf("Length of queue is %d. \n", Deque_size(d));
        d = Deque_removeFirst(d);
        Deque_printFromStart(d);
        d = Deque_removeLast(d);
        Deque_printFromLast(d);
    }
    
}