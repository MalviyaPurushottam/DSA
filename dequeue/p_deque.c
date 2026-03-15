#include "p_deque.h"
#include <stdio.h>
#include <stdlib.h>

Deque* Deque_create(void){
    Deque* d = (Deque*)malloc(sizeof(Deque));
    d->first = NULL;
    d->last = NULL;
    return d;
}

void Deque_delete(Deque* d){
    if(d->first != NULL && d->last != NULL){
        printf("Deque still not empty but freeing the memory ...\n");
        while(d->first){
            d = Deque_removeFirst(d);
        }
        while(d->last){
            d = Deque_removeLast(d);
        }
    }
    free(d);
}

Deque* Deque_insertFirst(Deque* d, node* data){
    deque_node* temp_node = (deque_node*)malloc(sizeof(deque_node));
    temp_node->node.data = data->data;
    temp_node->nxt = NULL;
    temp_node->prev = NULL;

    if((d->first == NULL) && (d->last == NULL)){
        d->first = temp_node;
        d->last = temp_node;
    }
    else{
        d->first->prev = temp_node;
        temp_node->nxt = d->first;
        d->first = temp_node;
    }

    return d;
}

Deque* Deque_insertLast(Deque* d, node* data){
    deque_node* temp_node = (deque_node*)malloc(sizeof(deque_node));
    temp_node->node.data = data->data;
    temp_node->nxt = NULL;
    temp_node->prev = NULL;

    if((d->first == NULL) && (d->last == NULL)){
        d->first = temp_node;
        d->last = temp_node;
    }
    else{
        d->last->nxt = temp_node;
        temp_node->prev = d->last;
        d->last = temp_node;
    }

    return d;
}

Deque* Deque_removeFirst(Deque* d){
    deque_node* temp = d->first;
    d->first = d->first->nxt;
    d->first->prev = NULL;
    free(temp);
    return d;
}

Deque* Deque_removeLast(Deque* d){
    deque_node* temp = d->last;
    d->last = d->last->prev;
    d->last->nxt = NULL;
    free(temp);
    return d;
}

node* Deque_first(Deque* d){
    if(d->first == NULL){
        return NULL;
    }
    return &(d->first->node);
}

node* Deque_last(Deque* d){
    if(d->last == NULL){
        return NULL;
    }
    return &(d->last->node);
}

int Deque_size(Deque* d){
    int count = 0;
    if(d->first == NULL && d->last == NULL){
        return 0;
    }
    if(d->first == d->last){
        return 1;
    }
    deque_node* temp = d->first;
    while(temp != NULL){
        temp = temp->nxt;
        count++;
    }
    return count;
}

void Deque_printFromStart(Deque* d){
    printf("Now print the queue form the start ... \nNULL -> ");
    deque_node* temp = d->first;
    while(temp != NULL){
        printf("%d -> ", temp->node.data);
        temp = temp->nxt;
    }
    printf("NULL \n");
    return;
}

void Deque_printFromLast(Deque* d){
    printf("Now print the queue form the end ... \nNULL -> ");
    deque_node* temp = d->last;
    while(temp != NULL){
        printf("%d -> ", temp->node.data);
        temp = temp->prev;
    }
    printf("NULL \n");
    return;
}
