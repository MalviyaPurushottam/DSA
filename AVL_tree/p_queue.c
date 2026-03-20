#include "p_queue.h"

queue* Q_create(void){
    queue* Q = (queue*) malloc(sizeof(queue));

    Q->head = NULL;
    Q->tail = NULL;

    return Q;
}

void Q_enqueue(queue* Q, void* node){
    q_node* ptr = (q_node*)malloc(sizeof(q_node));
    ptr->node_ptr = node;
    ptr->nxt = NULL;

    if(Q->head == NULL && Q->tail == NULL){
        Q->head = ptr;
        Q->tail = ptr;
        return;
    }
    else{
        Q->tail->nxt = ptr;
        Q->tail = ptr;
        return;
    }
}

void* Q_dequeue(queue* Q){
    if(Q->head == NULL){
        return NULL;
    }
    else {
        q_node* temp = Q->head;
        Q->head = Q->head->nxt;
        if(Q->head == NULL){
            Q->tail = NULL;
        }
        return temp->node_ptr;
    }
}

int Q_isEmpty(queue* Q){
    if(Q->head == NULL){
        return 0;
    }
    return 1;
}
int Q_size(queue* Q){
    int count = 0;
    q_node* temp = Q->head;
    while (temp != NULL) {
        count++;
        temp = temp->nxt;
    }
    return count;
}